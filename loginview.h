#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "mousemoveeventwindows.h"
namespace Ui {
class LoginView;
}

class LoginView : public mouseMoveEventWindows
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

    int getUserPassword();
    void initPassword();
    void rememberPassword();
    void showTipWnd(QString text);
    QWidget *getDragnWidget();
private:
    Ui::LoginView *ui;
    QLabel* tip;
    QTimer* timer;

public slots:
    void loginSystem();
    void openSignUpWnd();
    void openForgotPsdWnd();
};

#endif // LOGINVIEW_H
