#include <QApplication>
#include <QDesktopWidget>
#include <QtGui>
#include <QPainter>
#include <QFont>

#include "core/utils/global.h"

#include "osdBaseWidget.h"

#ifdef Q_OS_WIN
# include <windows.h>
#endif

#ifdef WITH_X11EXTRAS
# include <X11/Xlib.h>
# include <QX11Info>
# include <X11/extensions/shape.h>
#endif

OSDBaseWidget::OSDBaseWidget(QWidget *parent)
  : QWidget(parent, Qt::FramelessWindowHint)
  , offscreen(NULL)
{
    setAccessibleName("OSD");
    setWindowTitle("ViMouse OSD");
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    //showMaximized();
    setGeometry(QApplication::desktop()->screenGeometry(-1));


#ifdef Q_OS_WIN
    runOnTopCommand();
#endif

    setAttribute(Qt::WA_TranslucentBackground);
    show();

#ifdef WITH_X11EXTRAS
    QRect relativeWidgetRect = this->contentsRect();
    QRect absoluteWidgetRect = QRect(QWidget::mapToGlobal(relativeWidgetRect.topLeft()), QWidget::mapToGlobal(relativeWidgetRect.bottomRight()));

    XRectangle xrect = { 0, 0, 1, 1 };
    Display *display = QX11Info::display();
    Window winId = (Window)this->winId();

    XShapeCombineRectangles (
         display,
         winId,
         ShapeInput,
         absoluteWidgetRect.x(), absoluteWidgetRect.y(),
         &xrect, 1,
         ShapeSet,
         YXBanded );
#endif // WITH_X11EXTRAS

    // FIXME
    hide();
}

OSDBaseWidget::~OSDBaseWidget()
{
    delete_safe(offscreen);
}



#ifdef Q_OS_WIN
void OSDBaseWidget::runOnTopCommand()
{
    HWND hwnd = (HWND) winId();
//    LONG styles = GetWindowLong(hwnd, GWL_EXSTYLE);
//    SetWindowLong(hwnd, GWL_EXSTYLE, styles | WS_EX_TOPMOST );
    SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
//    SetWindowPos(hwnd, HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
}
#endif

#ifdef WITH_X11EXTRAS
void OSDBaseWidget::runOnTopCommand()
{
  /*  QX11Info qX11Info = this->x11Info();
    Display *display = qX11Info.display ();
    Window winId = (Window)this->winId();*/

   /* Qt::WindowFlags flags = windowFlags();
    flags &= (~Qt::WindowStaysOnTopHint);
    setWindowFlags( flags );*/

}
#endif // WITH_X11EXTRAS

void OSDBaseWidget::offscreenChanged(QImage *newOffscreen)
{
    QImage *oldOffscreen = offscreen;
    offscreen = newOffscreen;
    delete oldOffscreen;

    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags( flags );

/*#ifdef Q_OS_WIN*/
    static int hackCount = 0;
    if ((hackCount % 20) == 0)
    {
#ifdef WITH_X11EXTRAS
        runOnTopCommand();
#endif
    }
    hackCount++;
/*#endif*/

    this->update();
}

void OSDBaseWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F10)
    {
        emit resetState();
    }

    event->ignore();
}



void OSDBaseWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (offscreen == 0)
    {
        QFont font;
        font.setPixelSize(70);
        painter.setFont(font);
        QRect rect = this->rect();
        painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, "No Information");
    } else {
        painter.drawImage(0,0,*offscreen);
    }
}
