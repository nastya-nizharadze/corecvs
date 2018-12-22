#include "viGLAreaWidget.h"
#include "core/buffers/g12Buffer.h"

ViGLAreaWidget::ViGLAreaWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    mScheduleDelay(10)
{
    ui.setupUi(this);
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(update()));
}

void ViGLAreaWidget::initializeGL()
{
    emit askParentInitialize();
}

void ViGLAreaWidget::resizeGL(int width, int height)
{
    emit notifyParentResize(width, height);
}


void ViGLAreaWidget::mouseMoveEvent(QMouseEvent *event)
{
    emit notifyParentMouseMove(event);
}

void ViGLAreaWidget::mousePressEvent(QMouseEvent *event)
{
    emit notifyParentMousePress(event);
}

void ViGLAreaWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit notifyParentMouseRelease(event);
}

void ViGLAreaWidget::scheduleUpdate()
{
    // SYNC_PRINT(("ViGLAreaWidget::scheduleUpdate(): Called\n"));
    if (mTimer.isActive())
        return;
    mTimer.setSingleShot(true);
    mTimer.setInterval(mScheduleDelay);
    mTimer.start();
}

void ViGLAreaWidget::update()
{
    // SYNC_PRINT(("ViGLAreaWidget::update(): Called\n"));
    QOpenGLWidget::update();
    if (mTimer.isActive()) mTimer.stop();
}

void ViGLAreaWidget::setScheduleDelay(int delay)
{
    mScheduleDelay = delay;
}

void ViGLAreaWidget::paintGL()
{
    emit askParentRepaint();
}

void ViGLAreaWidget::wheelEvent ( QWheelEvent * event )
{
//    cout << "ViGLAreaWidget::wheelEvent" << endl;
    emit notifyParentWheelEvent(event);
}

void ViGLAreaWidget::keyPressEvent   ( QKeyEvent * event )
{
//    cout << "ViGLAreaWidget::keyPressEvent" << endl;
    emit notifyParentKeyPressEvent(event);
}

void ViGLAreaWidget::keyReleaseEvent ( QKeyEvent * event )
{
//    cout << "ViGLAreaWidget::keyReleaseEvent" << endl;
    emit notifyParentKeyReleaseEvent(event);
}


ViGLAreaWidget::~ViGLAreaWidget()
{

}
