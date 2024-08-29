#ifndef MOUSEMOVEEVENTWINDOWS
#define MOUSEMOVEEVENTWINDOWS
#include <QWidget>
class mouseMoveEventWindows:public QWidget
{
    Q_OBJECT
public:
    explicit mouseMoveEventWindows(QWidget *parent);
protected:
    //鼠标按下
    void mousePressEvent(QMouseEvent *event);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent *event);
    //释放鼠标
    void mouseReleaseEvent(QMouseEvent *event);
    //判断鼠标点击的位置是否进入可拖动区域
    bool isPointInDragnWidget(const QWidget*widget, const QPoint &point);
    //是否可移动
    bool isMove;
    //鼠标按下去的点
    QPoint pressedPoint;
    //获取可拖动控件，必须由子类指定
    virtual QWidget* getDragnWidget() = 0;
private:
    QPoint last;
};
#endif // !MOUSEMOVEEVEN
