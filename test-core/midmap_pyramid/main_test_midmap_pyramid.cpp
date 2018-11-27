/**
 * \file main_test_midmap_pyramid.cpp
 * \brief Add Comment Here
 *
 * \date Feb 25, 2010
 * \author alexander
 */

#include <stdlib.h>
#include "gtest/gtest.h"

#include "core/utils/global.h"

#include "core/buffers/g12Buffer.h"
#include "core/buffers/bufferFactory.h"
#include "core/fileformats/bmpLoader.h"
#include "core/buffers/mipmapPyramid.h"

#include <iostream>

#include "core/fileformats/bmpLoader.h"
#include "core/cameracalibration/cameraModel.h"

#include "core/geometry/mesh3d.h"
#include "core/buffers/rgb24/rgb24Buffer.h"
#include "core/geometry/renderer/simpleRenderer.h"

#include <core/cameracalibration/calibrationDrawHelpers.h>

using namespace corecvs;

TEST(MidmapPyramid, testFunction)
{
    G12Buffer *buffer = BufferFactory::getInstance()->loadG12Bitmap("chess.bmp");
    if (buffer == nullptr)
    {
        cout << "Could not open test image" << endl;
        return;
    }
    CORE_ASSERT_TRUE(buffer != NULL, "missed MidmapPyramid test data");

    int numLevels = 8;
    AbstractMipmapPyramid<G12Buffer> *pyr = new AbstractMipmapPyramid<G12Buffer>(buffer, numLevels, 1.2f);
    for (int i = 0; i < numLevels; i++)
    {
        char outName[256];
        snprintf2buf(outName, "pyr%d.bmp", i);

        G12Buffer *level = pyr->levels[i];
        RGB24Buffer levelSave(level);
        BMPLoader().save(string(outName), &levelSave);
        delete level;
    }
    delete_safe(pyr);
    delete buffer;
}

TEST(MidmapPyramid, testTexure)
{
    RGB24Buffer buffer(128, 128);
    RGBColor white = RGBColor::White();
    buffer.checkerBoard(16, white);

    BufferFactory::getInstance()->saveRGB24Bitmap(&buffer, "chess.bmp");

    int numLevels = 7;
    AbstractMipmapPyramid<RGB24Buffer> *pyramide = new  AbstractMipmapPyramid<RGB24Buffer>(&buffer, numLevels, 1);

    BMPLoader().save("chess6.bmp", pyramide->levels[6]);
    BMPLoader().save("chess5.bmp", pyramide->levels[5]);
    BMPLoader().save("chess4.bmp", pyramide->levels[4]);
    BMPLoader().save("chess3.bmp", pyramide->levels[3]);
    BMPLoader().save("chess2.bmp", pyramide->levels[2]);
    BMPLoader().save("chess1.bmp", pyramide->levels[1]);

    int h = 900;
    int w = 900;
    RGB24Buffer *bufferpic = new RGB24Buffer(h, w, RGBColor::White());

    ClassicRenderer renderer;
    PinholeCameraIntrinsics cam(Vector2dd(w,h), degToRad(50));
    renderer.modelviewMatrix = cam.getKMatrix();
    renderer.drawFaces = true;
    Mesh3DDecorated mesh;

    Vector3dd a01(-25.0, 10.0, -40.0);
    Vector3dd a02(-25.0, 0.0, -40.0);
    Vector3dd a03(-15.0, 0.0, -40.0);

    Vector3dd a11(-20.0, 10.0, -20.0);
    Vector3dd a12(-20.0, 0.0, -20.0);
    Vector3dd a13(-10.0, 0.0, -20.0);

    Vector3dd a21(-15.0, 10.0, 20.0);
    Vector3dd a22(-15.0, 0.0, 20.0);
    Vector3dd a23(-5.0, 0.0, 20.0);

    Vector3dd a31(-7.5, 10.0, 75.0);
    Vector3dd a32(-7.5, 0.0, 75.0);
    Vector3dd a33(3.5, 0.0, 75.0);

    Vector3dd a41(5.0, 10.0, 160.0);
    Vector3dd a42(5.0, 0.0, 160.0);
    Vector3dd a43(15.0, 0.0, 160.0);

    Vector3dd a51(25.0, 10.0, 320.0);
    Vector3dd a52(25.0, 0.0, 320.0);
    Vector3dd a53(35.0, 0.0, 320.0);

    Vector3dd a61(62.0, 10.0, 640.0);
    Vector3dd a62(62.0, 0.0, 640.0);
    Vector3dd a63(72.0, 0.0, 640.0);

    Vector3d32 a1(0, 0, -20);
    Vector3d32 a2(0, 0, -20);
    Vector3d32 a3(0, 0, -20);
    //Vector3d32 x(a1, a2, a3);
    //Vector4d32 b(0, 0, -20, 0);

    mesh.mulTransform(Affine3DQ::Shift(0, 0, 100));
    mesh.addTriangle(a01,a02,a03);
    mesh.addTriangle(a11,a12,a13);
    mesh.addTriangle(a21,a22,a23);
    mesh.addTriangle(a31,a32,a33);
    mesh.addTriangle(a41,a42,a43);
    mesh.addTriangle(a51,a52,a53);
    mesh.addTriangle(a61,a62,a63);
    mesh.popTransform();

    Vector2dd b1(0.0, 0.0);
    Vector2dd b2(10.0, 0.0);
    Vector2dd b3(0.0, 10.0);

    // mesh.hasTexCoords = true;
    // mesh.hasNormals = true;

    for (int i = 0; i < 7; i++){
        mesh.normalId[i][0] = 0;
        mesh.normalId[i][1] = 0;
        mesh.normalId[i][2] = 20;
        renderer.textures[0] = pyramide->levels[0];
        mesh.texId[i][0] = 0;
        mesh.texId[i][1] = 1;
        mesh.texId[i][2] = 2;
        mesh.texId[i][3] = 0;

        mesh.textureCoords[mesh.texId[i][0]] = b1;
        mesh.textureCoords[mesh.texId[i][1]] = b2;
        mesh.textureCoords[mesh.texId[i][2]] = b3;
    }

    renderer.render(&mesh, bufferpic);

    BMPLoader().save("trianglesdraw1.bmp", bufferpic);

    cout << buffer.elementBl(15.5, 15.5);
    CameraModel model;
    model.intrinsics.reset(cam.clone());
    model.setLocation(Affine3DQ::Identity());
    CalibrationDrawHelpers helper;
    helper.drawCamera(mesh, model, 0.5);
    mesh.dumpPLY("test.ply");

    delete_safe(bufferpic);

}
