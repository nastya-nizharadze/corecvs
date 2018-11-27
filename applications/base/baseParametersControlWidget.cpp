/**
 * \file baseParametersControlWidget.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

#include "baseParametersControlWidget.h"
#include "ui_baseParametersControlWidget.h"
#include <memory>
#include "qSettingsGetter.h"
#include "qSettingsSetter.h"


BaseParametersControlWidget::BaseParametersControlWidget(QWidget *parent, bool _autoInit, QString _rootPath)
    : ParametersControlWidgetBase(parent)
    , mUi(new Ui::BaseParametersControlWidget)
    , autoInit(_autoInit)
    , rootPath(_rootPath)
{
    mUi->setupUi(this);

    QObject::connect(mUi->rotationComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->mirrorCheckBox, SIGNAL(stateChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->swapCamerasButton, SIGNAL(clicked(bool)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->filterLockButton, SIGNAL(clicked(bool)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->enableFilterGraphCheckBox, SIGNAL(stateChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->downsampleSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->hSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->wSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->autoHCheckBox, SIGNAL(stateChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->autoWCheckBox, SIGNAL(stateChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->xSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->ySpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(paramsChanged()));
    QObject::connect(mUi->interpolationTypeComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(paramsChanged()));
}

BaseParametersControlWidget::~BaseParametersControlWidget()
{

    delete mUi;
}

void BaseParametersControlWidget::loadParamWidget(WidgetLoader &loader)
{
    std::unique_ptr<BaseParameters> params(createParameters());
    loader.loadParameters(*params, rootPath);
    setParameters(*params);
}

void BaseParametersControlWidget::saveParamWidget(WidgetSaver  &saver)
{
    saver.saveParameters(*std::unique_ptr<BaseParameters>(createParameters()), rootPath);
}

void BaseParametersControlWidget::getParameters(BaseParameters& params) const
{
    params = *std::unique_ptr<BaseParameters>(createParameters());
}


BaseParameters *BaseParametersControlWidget::createParameters() const
{

    /**
     * We should think of returning parameters by value or saving them in a preallocated place
     **/


    return new BaseParameters(
          static_cast<RotationPresets::RotationPresets>(mUi->rotationComboBox->currentIndex())
        , mUi->mirrorCheckBox->isChecked()
        , mUi->swapCamerasButton->isChecked()
        , mUi->filterLockButton->isChecked()
        , mUi->enableFilterGraphCheckBox->isChecked()
        , mUi->downsampleSpinBox->value()
        , mUi->hSpinBox->value()
        , mUi->wSpinBox->value()
        , mUi->autoHCheckBox->isChecked()
        , mUi->autoWCheckBox->isChecked()
        , mUi->xSpinBox->value()
        , mUi->ySpinBox->value()
        , static_cast<InterpolationType::InterpolationType>(mUi->interpolationTypeComboBox->currentIndex())
    );
}

void BaseParametersControlWidget::setParameters(const BaseParameters &input)
{
    // Block signals to send them all at once
    bool wasBlocked = blockSignals(true);
    mUi->rotationComboBox->setCurrentIndex(input.rotation());
    mUi->mirrorCheckBox->setChecked(input.mirror());
    mUi->swapCamerasButton->setChecked(input.swapCameras());
    mUi->filterLockButton->setChecked(input.filterLock());
    mUi->enableFilterGraphCheckBox->setChecked(input.enableFilterGraph());
    mUi->downsampleSpinBox->setValue(input.downsample());
    mUi->hSpinBox->setValue(input.h());
    mUi->wSpinBox->setValue(input.w());
    mUi->autoHCheckBox->setChecked(input.autoH());
    mUi->autoWCheckBox->setChecked(input.autoW());
    mUi->xSpinBox->setValue(input.x());
    mUi->ySpinBox->setValue(input.y());
    mUi->interpolationTypeComboBox->setCurrentIndex(input.interpolationType());
    blockSignals(wasBlocked);
    emit paramsChanged();
}

void BaseParametersControlWidget::setParametersVirtual(void *input)
{
    // Modify widget parameters from outside
    BaseParameters *inputCasted = static_cast<BaseParameters *>(input);
    setParameters(*inputCasted);
}
