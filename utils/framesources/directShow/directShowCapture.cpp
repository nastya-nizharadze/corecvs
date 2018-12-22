/**
 * \file directShowCapture.cpp
 * \brief Capture camera video stream using DirectShow
 *
 * \date Jul 15, 2010
 * \author apimenov
 */
#include "directShowCapture.h"
#include "core/framesources/decoders/mjpegDecoderLazy.h"
#include "core/utils/preciseTimer.h"
#include "core/utils/log.h"

#include <sstream>

#include <QtCore/QRegExp>


void DirectShowCaptureInterface::init(const string &devname, int h, int w, int fps,  bool isRgb, int bpp, int compressed)
{
    CORE_ASSERT_TRUE_P((uint)compressed < DirectShowCameraDescriptor::codec_size, ("invalid 'compressed' in DirectShowCaptureInterface::init()"));

    mAutoFormat = false;

    std::stringstream ss;
    ss << devname << ":1/"
        << fps << ":"
        << DirectShowCameraDescriptor::codec_names[compressed] << ":"
        << w << "x" << h;
    //mDevname = QString("%1:1/%2:%3:%4x%5")
    //    .arg(devname.c_str())
    //    .arg(fps)
    //    .arg(DirectShowCameraDescriptor::codec_names[compressed])
    //    .arg(w)
    //    .arg(h)
    //    .toStdString();
    mDevname = ss.str();

    mDeviceIDs[LEFT_FRAME] = atoi(devname.c_str());
    mDeviceIDs[RIGHT_FRAME] = -1;

    for (int i = 0; i < MAX_INPUTS_NUMBER; i++)
    {
        mFormats[i].type   = DirectShowCameraDescriptor::codec_types[compressed];
        mFormats[i].height = h;
        mFormats[i].width  = w;
        mFormats[i].fps    = fps;
        mFormats[i].bpp    = bpp;
    }

    mCompressed  = compressed;
    mIsRgb       = isRgb;
    skippedCount = 0;
    isRunning    = false;
}

void DirectShowCaptureInterface::initForAutoFormat(const string &devname, int h, int w, int fps, bool isRgb)
{
    mAutoFormat = true;
    mDevname = devname;

    mDeviceIDs[LEFT_FRAME] = atoi(devname.c_str());
    mDeviceIDs[RIGHT_FRAME] = -1;

    for (int i = 0; i < MAX_INPUTS_NUMBER; i++)
    {
        mFormats[i].type   = AUTOSELECT_FORMAT_FEATURE;
        mFormats[i].height = h;
        mFormats[i].width  = w;
        mFormats[i].fps    = fps;
        mFormats[i].bpp    = AUTOSELECT_FORMAT_FEATURE;
    }

    mIsRgb       = isRgb;
    skippedCount = 0;
    isRunning    = false;
}

DirectShowCaptureInterface::DirectShowCaptureInterface(const string &devname, int h, int w, int fps, bool isRgb)
{
    initForAutoFormat(devname, h, w, fps, isRgb);
}

DirectShowCaptureInterface::DirectShowCaptureInterface(const string &devname, ImageCaptureInterface::CameraFormat inFormat, bool isRgb)
{
    initForAutoFormat(devname, inFormat.height, inFormat.width, inFormat.fps, isRgb);
}

DirectShowCaptureInterface::DirectShowCaptureInterface(const string &devname, bool isRgb)
{
    mDevname = devname;
    mIsRgb   = isRgb;
    mAutoFormat = false;

    //     Group Number                   1       2 3        4 5      6       7 8       9       10     11        1213     14
    QRegExp deviceStringPattern("^([^,:]*)(,([^:]*))?(:(\\d*)/(\\d*))?((:mjpeg)|(:yuyv)|(:rgb)|(:fjpeg))?(:(\\d*)x(\\d*))?$");
    static const int Device1Group     = 1;
    static const int Device2Group     = 3;
    static const int FpsNumGroup      = 5;
    static const int FpsDenumGroup    = 6;
    static const int CompressionGroup = 7;
    static const int WidthGroup       = 13;
    static const int HeightGroup      = 14;

    L_DDEBUG_P("Input string <%s>", devname.c_str());

    int result = deviceStringPattern.indexIn(devname.c_str());
    if (result == -1)
    {
        L_ERROR_P("Error in device string format:<%s>", devname.c_str());
        return;
    }
    L_INFO_P("Parsed data:\n"
             "  | - Device 1=%s\n"
             "  | - Device 2=%s\n"
             "  | - FPS %s/%s\n"
             "  | - Size [%sx%s]\n"
             "  \\ - Compressing: %s\n"
             "RGB decoding is %s",
             deviceStringPattern.cap(Device1Group).toLatin1().constData(),
             deviceStringPattern.cap(Device2Group).toLatin1().constData(),
             deviceStringPattern.cap(FpsNumGroup).toLatin1().constData(),
             deviceStringPattern.cap(FpsDenumGroup).toLatin1().constData(),
             deviceStringPattern.cap(WidthGroup).toLatin1().constData(),
             deviceStringPattern.cap(HeightGroup).toLatin1().constData(),
             deviceStringPattern.cap(CompressionGroup).toLatin1().constData(),
             mIsRgb ? "on" : "off"
    );

    mDeviceIDs[Frames::LEFT_FRAME ] = deviceStringPattern.cap(Device1Group).isEmpty() ? -1 : deviceStringPattern.cap(Device1Group).toInt();
    mDeviceIDs[Frames::RIGHT_FRAME] = deviceStringPattern.cap(Device2Group).isEmpty() ? -1 : deviceStringPattern.cap(Device2Group).toInt();

    bool err;
    int fpsnum = deviceStringPattern.cap(FpsNumGroup).toInt(&err);
    if (!err) fpsnum = 1;

    int fpsdenum = deviceStringPattern.cap(FpsDenumGroup).toInt(&err);
    if (!err) fpsdenum = 10;

    int width = deviceStringPattern.cap(WidthGroup).toInt(&err);
    if (!err || width <= 0) width = 800;

    int height = deviceStringPattern.cap(HeightGroup).toInt(&err);
    if (!err || height <= 0) height = 600;

    mCompressed = DirectShowCameraDescriptor::UNCOMPRESSED_YUV;
    if (!deviceStringPattern.cap(CompressionGroup).isEmpty())
    {
       if      (!deviceStringPattern.cap(CompressionGroup).compare(QString(":rgb"))) {
           mCompressed = DirectShowCameraDescriptor::UNCOMPRESSED_RGB;
           mIsRgb   = true;
       }
       else if (!deviceStringPattern.cap(CompressionGroup).compare(QString(":mjpeg"))) {
           mCompressed = DirectShowCameraDescriptor::COMPRESSED_JPEG;
       }
       else if (!deviceStringPattern.cap(CompressionGroup).compare(QString(":fjpeg"))) {
           mCompressed = DirectShowCameraDescriptor::COMPRESSED_FAST_JPEG;
       }
    }

    for (int i = 0; i < Frames::MAX_INPUTS_NUMBER; i++)
    {
        L_INFO_P("Capture %s device: DShow:%d", Frames::getEnumName((Frames::FrameSourceId)i), mDeviceIDs[i]);
    }
    L_INFO_P("Format is: %s", DirectShowCameraDescriptor::codec_names[mCompressed]);

    /* TODO: Make cycle here */
    for (int i = 0; i < Frames::MAX_INPUTS_NUMBER; i++)
    {
        mFormats[i].type = DirectShowCameraDescriptor::codec_types[mCompressed];
        mFormats[i].height = height;
        mFormats[i].width  = width;
        mFormats[i].fps    = (int)((double)fpsdenum / fpsnum);
    }

    skippedCount = 0;
    isRunning = false;
}

ImageCaptureInterface::CapErrorCode DirectShowCaptureInterface::initCapture()
{
    for (int i = 0; i < Frames::MAX_INPUTS_NUMBER; i++)
    {
        mCameras[i].deviceHandle = mDeviceIDs[i] >= 0 ? DirectShowCapDll_initCapture(mDeviceIDs[i]) : -1;
    }

    string devname = mDevname;

    for (int i = 0; i < Frames::MAX_INPUTS_NUMBER; i++)
    {
        if (!isCorrectDeviceHandle(i))
        {
            mAutoFormat = i < Frames::MAX_INPUTS_NUMBER - 1;
            continue;
        }

        if (mAutoFormat)
        {
            int format = selectCameraFormat(mFormats[i].height, mFormats[i].width);
            int bpp = format == DirectShowCameraDescriptor::UNCOMPRESSED_RGB ? PREFFERED_RGB_BPP : AUTOSELECT_FORMAT_FEATURE;
            init(devname, mFormats[i].height, mFormats[i].width, mFormats[i].fps, mIsRgb, bpp, format);
            mAutoFormat = i < Frames::MAX_INPUTS_NUMBER - 1;
        }

        if (DirectShowCapDll_setFormat(mCameras[i].deviceHandle, &mFormats[i]) != 0)
        {
            //printf("Failed to set format\n");
        }
        DirectShowCapDll_setFrameCallback(mCameras[i].deviceHandle, this, DirectShowCaptureInterface::callback);
    }

    if (isCorrectDeviceHandle(0) && isCorrectDeviceHandle(1))
        return ImageCaptureInterface::SUCCESS;
    if (isCorrectDeviceHandle(0) || isCorrectDeviceHandle(1))
        return ImageCaptureInterface::SUCCESS_1CAM;
    return ImageCaptureInterface::FAILURE;
}

bool DirectShowCaptureInterface::getCurrentFormat(CameraFormat &format)
{
    bool toReturn = false;
    L_DDEBUG_P("Real Formats:");
    for (int i = 0; i < Frames::MAX_INPUTS_NUMBER; i++)
    {
        if (!isCorrectDeviceHandle(i))
            continue;

        DirectShowCapDll_printSimpleFormat(&mFormats[i]);

        format = CameraFormat(mFormats[i].height, mFormats[i].width, mFormats[i].fps);
        toReturn = true;
    }
    return toReturn;
}

void DirectShowCaptureInterface::callback(void *thiz, DSCapDeviceId dev, FrameData data)
{
    //SYNC_PRINT(("Received new frame in a callback\n"));
    DirectShowCaptureInterface *pInterface = static_cast<DirectShowCaptureInterface *>(thiz);
    pInterface->memberCallback(dev, data);
}

ALIGN_STACK_SSE void DirectShowCaptureInterface::memberCallback(DSCapDeviceId dev, FrameData data)
{
    //SYNC_PRINT(("Received new frame in a member %d\n", dev));
    std::lock_guard<std::mutex> locker(mProtectFrame);

    DirectShowCameraDescriptor *camera = NULL;
    if (mCameras[0].deviceHandle == dev) camera = &mCameras[0];
    else
    if (mCameras[1].deviceHandle == dev) camera = &mCameras[1];
    else
        return;

    PreciseTimer timer = PreciseTimer::currentTime();
    camera->gotBuffer = true;
    camera->timestamp = (data.timestamp + 5) / 10;
    delete_safe (camera->buffer);
    delete_safe (camera->buffer24);

    if (data.format.type == CAP_YUV || data.format.type == CAP_UYVY)
    {
        bool uyvy = data.format.type == CAP_UYVY;
        if (mIsRgb) {
            camera->buffer24 = new RGB24Buffer(data.format.height, data.format.width, false);
            camera->buffer24->fillWithYUVFormat((uint8_t *)data.data, uyvy);
        }
        else {
            if(!uyvy)
            {
                camera->buffer = new G12Buffer(data.format.height, data.format.width, false);
                camera->buffer->fillWithYUYV((uint16_t *)data.data);
            }
            else
            {
                //TODO: to be replaced by UYVU->G12 converter as soon as it's implemented
                RGB24Buffer *rgbBuffer = new RGB24Buffer(data.format.height, data.format.width, false);
                rgbBuffer->fillWithYUVFormat((uint8_t *)data.data, uyvy);
                camera->buffer = rgbBuffer->toG12Buffer();
                delete_safe (rgbBuffer);
            }
        }
    }
    else if (data.format.type == CAP_MJPEG)
    {
        MjpegDecoderLazy *lazyDecoder = new MjpegDecoderLazy;   // don't place it at stack, it's too huge!
        if (mIsRgb)
            camera->buffer24 = lazyDecoder->decodeRGB24((uchar *)data.data);
        else
            camera->buffer   = lazyDecoder->decode((uchar *)data.data);
        delete lazyDecoder;
    }
    else if (data.format.type == CAP_RGB)
    {
        if(3 * (data.format.height - 1) * data.format.width >= data.size)
        {
            L_INFO_P("Driver returned inconsistent data. %ld bytes recived.", data.size);
        }
        else if (mIsRgb) {
            camera->buffer24 = new RGB24Buffer(data.format.height, data.format.width, true);
            int w = camera->buffer24->w;
            int h = camera->buffer24->h;
            for (int i = 0; i < h; i++) {
                uint8_t  *rgbData = ((uint8_t *)data.data) + 3 * (h - i - 1) * w;
                RGBColor *rgb24Data = &(camera->buffer24->element(i, 0));
                for (int j = 0; j < w; j++) {
                    RGBColor rgb(rgbData[2], rgbData[1], rgbData[0]);   // the given data format has B,G,R order
                    *rgb24Data++ = rgb;
                    rgbData += 3;
                }
            }
        }
        else {
            camera->buffer = new G12Buffer(data.format.height, data.format.width, false);
            int w = camera->buffer->w;
            int h = camera->buffer->h;
            for (int i = 0; i < h; i++) {
                uint8_t  *rgbData = ((uint8_t *)data.data) + 3 * (h - i - 1) * w;
                uint16_t *greyData = &(camera->buffer->element(i, 0));
                for (int j = 0; j < w; j++) {
                    RGBColor rgb(rgbData[2], rgbData[1], rgbData[0]);   // the given data format has B,G,R order
                    *greyData++ = rgb.luma12();
                    rgbData += 3;
                }
            }
        }
    }
    else {
        camera->buffer = new G12Buffer(data.format.height, data.format.width, false);
    }

    camera->decodeTime = timer.usecsToNow();
    /* If both frames are in place */

    if (mCameras[0].gotBuffer && mCameras[1].gotBuffer)
    {
        mCameras[0].gotBuffer = false;
        mCameras[1].gotBuffer = false;

        CaptureStatistics stats;
        int64_t desync = mCameras[0].timestamp - mCameras[1].timestamp;
        stats.values[CaptureStatistics::DESYNC_TIME] = desync > 0 ? desync : -desync;
        stats.values[CaptureStatistics::DECODING_TIME] = mCameras[0].decodeTime + mCameras[1].decodeTime;
        if (lastFrameTime.usecsTo(PreciseTimer()) != 0)
        {
            stats.values[CaptureStatistics::INTERFRAME_DELAY] = lastFrameTime.usecsToNow();
        }
        lastFrameTime = PreciseTimer::currentTime();

        frame_data_t frameData;
        frameData.timestamp = mCameras[0].timestamp / 2 + mCameras[1].timestamp / 2;

        if (imageInterfaceReceiver != NULL)
        {
            imageInterfaceReceiver->newFrameReadyCallback(frameData);
            imageInterfaceReceiver->newStatisticsReadyCallback(stats);
        }
    }
    else {
        frame_data_t frameData;
        frameData.timestamp = mCameras[0].timestamp;

        if (imageInterfaceReceiver != NULL)
        {
            imageInterfaceReceiver->newFrameReadyCallback(frameData);
        }

        //newStatisticsReady(stats);
        skippedCount++;
    }
}

ImageCaptureInterface::FramePair DirectShowCaptureInterface::getFrame()
{
    std::lock_guard<std::mutex> locker(mProtectFrame);

    FramePair result;
    if (mCameras[0].buffer != NULL)
    {
        result.setBufferLeft(new G12Buffer(mCameras[0].buffer));
    }
    if (mCameras[1].buffer != NULL)
    {
        result.setBufferRight(new G12Buffer(mCameras[1].buffer));
    }
    result.setTimeStampLeft (mCameras[0].timestamp);
    result.setTimeStampRight(mCameras[1].timestamp);
    return result;
}

ImageCaptureInterface::FramePair DirectShowCaptureInterface::getFrameRGB24()
{
    std::lock_guard<std::mutex> locker(mProtectFrame);

    FramePair result;
    if (mCameras[0].buffer != NULL)
    {
        result.setBufferLeft(new G12Buffer(mCameras[0].buffer));
    }
    if (mCameras[1].buffer != NULL)
    {
        result.setBufferRight(new G12Buffer(mCameras[1].buffer));
    }
    if (mCameras[0].buffer24 != NULL)
    {
        result.setRgbBufferLeft(new RGB24Buffer(mCameras[0].buffer24));
    }
    if (mCameras[1].buffer24 != NULL)
    {
        result.setRgbBufferRight(new RGB24Buffer(mCameras[1].buffer24));
    }
    result.setTimeStampLeft (mCameras[0].timestamp);
    result.setTimeStampRight(mCameras[1].timestamp);
    return result;
}

ImageCaptureInterface::CapErrorCode DirectShowCaptureInterface::startCapture()
{
    isRunning = true;
    if (isCorrectDeviceHandle(0))
    {
        DirectShowCapDll_start(mCameras[0].deviceHandle);
    }
    if (isCorrectDeviceHandle(1))
    {
        DirectShowCapDll_start(mCameras[1].deviceHandle);
    }
    //spin.start();
    return ImageCaptureInterface::SUCCESS;
}

DirectShowCaptureInterface::~DirectShowCaptureInterface()
{
    if (isRunning)
    {
        /*
            Callback is set safe and synchroniously,
            so after the call of the callback reset, we will never again
            receive a frame. So it will be safe to destroy the object
        */
        for (int i = 0; i < Frames::MAX_INPUTS_NUMBER; i++)
        {
            if (isCorrectDeviceHandle(i))
            {
                DirectShowCapDll_stop(mCameras[i].deviceHandle);
            }
        }
        isRunning = false;
    }

    for (int i = 0; i < Frames::MAX_INPUTS_NUMBER; i++)
    {
        if (isCorrectDeviceHandle(i))
        {
            delete_safe(mCameras[i].buffer);
            delete_safe(mCameras[i].buffer24);

            DirectShowCapDll_setFrameCallback(mCameras[i].deviceHandle, NULL, NULL);
            DirectShowCapDll_deinit(mCameras[i].deviceHandle);
            mCameras[i].deviceHandle = -1;
        }
    }
}

ImageCaptureInterface::CapErrorCode DirectShowCaptureInterface::queryCameraParameters(CameraParameters &parameters)
{
    if (isCorrectDeviceHandle(0))
    {
        mCameras[0].queryCameraParameters(parameters);
    }
    return ImageCaptureInterface::SUCCESS;
}

ImageCaptureInterface::CapErrorCode DirectShowCaptureInterface::setCaptureProperty(int id, int value)
{
    if (isCorrectDeviceHandle(0))
    {
        mCameras[0].setCaptureProperty(id, value);
    }
    if (isCorrectDeviceHandle(1))
    {
        mCameras[1].setCaptureProperty(id, value);
    }
    return ImageCaptureInterface::SUCCESS;
}

ImageCaptureInterface::CapErrorCode DirectShowCaptureInterface::getCaptureProperty(int id, int *value)
{
    if (isCorrectDeviceHandle(0))
    {
        mCameras[0].getCaptureProperty(id, value);
    }
    return ImageCaptureInterface::SUCCESS;
}

ImageCaptureInterface::CapErrorCode DirectShowCaptureInterface::getCaptureName(std::string &value)
{
    if (!isCorrectDeviceHandle(0))
        return ImageCaptureInterface::FAILURE;

    char *name = NULL;
    if (DirectShowCapDll_deviceName(mCameras[0].deviceHandle, &name))
        return ImageCaptureInterface::FAILURE;

    value = name;
    return ImageCaptureInterface::SUCCESS;
}

ImageCaptureInterface::CapErrorCode DirectShowCaptureInterface::getFormats(int *num, CameraFormat *&formats)
{
    int number;
    CaptureTypeFormat* captureTypeFormats = nullptr;
    if(getCaptureFormats(number, captureTypeFormats) == ImageCaptureInterface::FAILURE)
    {
        return ImageCaptureInterface::FAILURE;
    }
    *num = number;
    delete formats;
    formats = new CameraFormat[number];

    for (int i = 0; i < number; i++)
    {
        formats[i] = CameraFormat(captureTypeFormats[i].height, captureTypeFormats[i].width, captureTypeFormats[i].fps);
    }

    delete[] captureTypeFormats;
    return ImageCaptureInterface::SUCCESS;
}

std::string DirectShowCaptureInterface::getInterfaceName()
{
    return std::string("dshow:") + mDevname;
}

DirectShowCaptureInterface::CapErrorCode DirectShowCaptureInterface::getDeviceName(int num, string &name)
{
    if (num < 0 || num >= 2)
    {
        return ImageCaptureInterface::FAILURE;
    }
    //     Group Number                   1       2 3        4 5      6       7 8       9       10     11        1213     14
    QRegExp deviceStringPattern(QString("^([^,:]*)(,([^:]*))?(:(\\d*)/(\\d*))?((:mjpeg)|(:yuyv)|(:rgb)|(:fjpeg))?(:(\\d*)x(\\d*))?$"));
    static const int Device1Group     = 1;
    static const int Device2Group     = 3;
    QString qdevname(mDevname.c_str());
    int result = deviceStringPattern.indexIn(qdevname);
    if (result == -1)
    {
        L_ERROR_P("Error in device string format:<%s>", mDevname.c_str());
        return ImageCaptureInterface::FAILURE;
    }
    if (num == 0)
    {
        name = deviceStringPattern.cap(Device1Group).toStdString();
    }
    else
    {
        name = deviceStringPattern.cap(Device2Group).toStdString();
    }
    return ImageCaptureInterface::SUCCESS;
}

string DirectShowCaptureInterface::getDeviceSerial(int num)
{
    CORE_UNUSED(num);
    return "-unsupported-";                                 // first minus is very important!
}

// Logging
void LogCallback(LogLevel level, const char* format, ...)
{
    va_list marker;
    va_start(marker, format);
    size_t len = vsnprintf(NULL, 0, format, marker) + 1;    // to add a nul symbol
    va_end(marker);

    va_list marker2;
    va_start(marker2, format);

    char* buf = new char[len];
    vsnprintf(buf, len, format, marker2);

    va_end(marker2);

    ::Log().log((Log::LogLevel)level, "dShowCapture", __LINE__, "capdll") << buf;
    delete[] buf;
}

void DirectShowCaptureInterface::getAllCameras(vector<string> &cameras)
{
    DirectShowCapDll_setLogger(LogCallback);

    int num = 0;
    DirectShowCapDll_devicesNumber(&num);
    for (int i = 0; i < num; i++)
    {
        cameras.push_back(std::to_string(i));
    }
}

bool DirectShowCaptureInterface::isCorrectDeviceHandle(int cameraNum)
{
    return mCameras[cameraNum].deviceHandle >= 0;
}

ImageCaptureInterface::CapErrorCode DirectShowCaptureInterface::getCaptureFormats(int &number, CaptureTypeFormat *&list)
{
    if(list != nullptr)
        delete_safe(list);
    number = 0;
    if (!isCorrectDeviceHandle(0))
        return ImageCaptureInterface::FAILURE;

    if (0 != DirectShowCapDll_getFormatNumber(mCameras[0].deviceHandle, &number))
    {
        L_ERROR_P("Error to get number of supported formats for cameraId: %d", (int)mCameras[0].deviceHandle);
        return ImageCaptureInterface::FAILURE;
    }

    CaptureTypeFormat* captureTypeFormats = new CaptureTypeFormat[number];

    if (0 != DirectShowCapDll_getFormats(mCameras[0].deviceHandle, number, captureTypeFormats))
    {
        delete[] captureTypeFormats;
        L_ERROR_P("Error to get supported formats for cameraId: %d", (int)mCameras[0].deviceHandle);
        return ImageCaptureInterface::FAILURE;
    }
    list = captureTypeFormats;
    return ImageCaptureInterface::SUCCESS;
}

DirectShowCaptureInterface::CapErrorCode DirectShowCaptureInterface::getCameraFormatsForResolution(int h, int w, std::vector<CAPTURE_FORMAT_TYPE> &formats)
{
    formats.clear();

    int number;
    CaptureTypeFormat* captureTypeFormats = nullptr;
    if (getCaptureFormats(number, captureTypeFormats)  == ImageCaptureInterface::FAILURE)
        return ImageCaptureInterface::FAILURE;

    for (int i = 0; i < number; i++)
    {
        if (captureTypeFormats[i].height == h &&
            captureTypeFormats[i].width == w)
        {
            formats.push_back((CAPTURE_FORMAT_TYPE)captureTypeFormats[i].type);
        }
    }
    return formats.size() ? ImageCaptureInterface::SUCCESS : ImageCaptureInterface::FAILURE;
}

int DirectShowCaptureInterface::selectCameraFormat(int h, int w)
{
    std::vector<CAPTURE_FORMAT_TYPE> formats;
    bool canRGB = false;
    bool canYUV = false;
    bool canUYVY = false;
    getCameraFormatsForResolution(h, w, formats);

    for (CAPTURE_FORMAT_TYPE format : formats)
    {
        switch (format)
        {
        case CAP_RGB:
            canRGB = true;
            break;
        case CAP_YUV:
            canYUV = true;
            break;
        case CAP_UYVY:
            canUYVY = true;
        }
    }
    if (canRGB)
        return DirectShowCameraDescriptor::UNCOMPRESSED_RGB;
    if (canYUV)
        return DirectShowCameraDescriptor::UNCOMPRESSED_YUV;
    if (canUYVY)
        return DirectShowCameraDescriptor::UNCOMPRESSED_UYVY;

    L_ERROR_P("Error to get supported formats for cameraId: %d. Try RGB", (int)mCameras[0].deviceHandle);
    return DirectShowCameraDescriptor::UNCOMPRESSED_RGB;
}
