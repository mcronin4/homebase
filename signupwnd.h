#ifndef SIGNUPWND_H
#define SIGNUPWND_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "mousemoveeventwindows.h"
namespace Ui {
class SignUpWnd;
}

class SignUpWnd : public mouseMoveEventWindows
{
    Q_OBJECT

public:
    explicit SignUpWnd(QWidget *parent = nullptr);
    ~SignUpWnd();

    bool isExisted(QString nType, const QString &value);
    void showTipWnd(QString text);
    QWidget *getDragnWidget();
private:
    Ui::SignUpWnd *ui;
    QLabel* tip;
    QTimer* timer;
public slots:
    void openLoginWnd();
    void signupProcess();
};

#endif // SIGNUPWND_H
