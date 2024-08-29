#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QWidget>
#include <QLabel>
#include "mousemoveeventwindows.h"
namespace Ui {
class ForgotPassword;
}

class ForgotPassword : public mouseMoveEventWindows
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = nullptr);
    ~ForgotPassword();

    void showTipWnd(QString text);
    void setShowPassword(QString str);
    QWidget *getDragnWidget();
public slots:
    void openLoginWnd();
    void getPassword();
private:
    Ui::ForgotPassword *ui;
    QLabel* tip;
    QTimer* timer;
};

#endif // FORGOTPASSWORD_H
