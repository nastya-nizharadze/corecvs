#ifndef _SCANNER_DIALOG_H_
#define _SCANNER_DIALOG_H_

/**
 * \file scannerDialog.h
 * \brief Defines a scanner dialog class derived from BaseHostDialog
 *
 */

#include <QString>

#include "core/utils/global.h"

#include "baseHostDialog.h"
#include "scannerThread.h"
#include "scannerParametersControlWidget.h"
#include "cloudViewDialog.h"
#include "scannercontrol.h"
#include "graphPlotDialog.h"

#define UI_NAME_SCANNER "scanner"

class ScannerDialog : public BaseHostDialog
{
    Q_OBJECT

public:

    ScannerDialog();
    ~ScannerDialog();


    virtual void initParameterWidgets();
    virtual void createCalculator();
    virtual void connectFinishedRecalculation();

    void addScannerPath(QString scannerPath);

signals:
    void recordingTriggered();
    void recordingReset();

public slots:
    void openPathSelectDialog();
   // void toggleRecording();
  //  void resetRecording();
    void scanningStateChanged(ScannerThread::ScanningState);
    void scannerControlParametersChanged(QSharedPointer<ScannerParameters> params);

    virtual void processResult();

    void errorMessage(QString message);

    void homeingWaitingFinished();
    void laserOn();
    void laserOff();
 //   void startscan();
private:
    bool mIsScanning;



    ScannerControl scanCtrl;

    ScannerParametersControlWidgetAdv *mScannerParametersControlWidget;

    QSharedPointer<ScannerParameters> mScannerControlParams;

    CloudViewDialog *cloud = NULL;
    GraphPlotDialog *graph = NULL;
    GraphPlotDialog *graphConvolution = NULL;
    AdvancedImageWidget *addImage = NULL;
    AdvancedImageWidget *brightImage = NULL;
    AdvancedImageWidget *channelImage = NULL;
    AdvancedImageWidget *cornerImage = NULL;

};

#endif // _SCANNER_DIALOG_H_
