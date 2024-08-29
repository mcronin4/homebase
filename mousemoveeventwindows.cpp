
#include "mouseMoveEventWindows.h"
#include <QMouseEvent>

mouseMoveEventWindows::mouseMoveEventWindows(QWidget *parent)

{
    isMove = false;

    this->setWindowFlags(Qt::FramelessWindowHint);

    //	setAttribute(Qt::WA_TranslucentBackground);


}

void mouseMoveEventWindows::mousePressEvent(QMouseEvent *event)
{

    bool shouldMove = isPointInDragnWidget(getDragnWidget(), event->pos());

    if (shouldMove){
        pressedPoint = event->pos();
        isMove = true;
    }

    event->ignore();
}
void mouseMoveEventWindows::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() == Qt::LeftButton) && isMove == true){

        QPoint currPoint = this->pos();
        currPoint.setX(currPoint.x() + event->x() - pressedPoint.x());
        currPoint.setY(currPoint.y() + event->y() - pressedPoint.y());
        this->move(currPoint);
    }
}

void mouseMoveEventWindows::mouseReleaseEvent(QMouseEvent *event)
{
    isMove = false;
}

bool mouseMoveEventWindows::isPointInDragnWidget(const QWidget *widget, const QPoint &point)
{

    QRect rect = widget->rect();

    bool isIn = point.x() >= rect.left() && point.x() <= rect.right() && point.y() >= rect.top() && point.y() <= rect.bottom();

    return isIn;
}
