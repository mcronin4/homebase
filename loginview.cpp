#include "loginview.h"
#include "ui_loginview.h"
#include "datamanage.h"
#include "signupwnd.h"
#include "forgotpassword.h"
#include "mainsystem.h"
#include <QRegularExpression>

LoginView::LoginView(QWidget *parent) :
    mouseMoveEventWindows(parent),
    ui(new Ui::LoginView)
    , tip(nullptr)
    , timer(nullptr)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    initPassword();
    connect(ui->loginBtn,&QPushButton::clicked,this,&LoginView::loginSystem);
    connect(ui->forgotPsdButton,&QPushButton::clicked,this,&LoginView::openForgotPsdWnd);
    connect(ui->closedBtn,&QPushButton::clicked,this,[this]{
        this->close();
    });


    connect(ui->commandLinkButton,&QCommandLinkButton::clicked,this,&LoginView::openSignUpWnd);
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[&]{
        if(tip)
            tip->hide();
    });
}


LoginView::~LoginView()
{
    delete ui;
}

QWidget *LoginView::getDragnWidget()
{
    return ui->widget;
}


int LoginView::getUserPassword()
{
    QString email = ui->emailEdit->text();
    QString password = ui->passwordEdit->text();

    if(email == "" || password == "")
    {
        showTipWnd("Input cannot be null");
        return FAIL;
    }

    QRegularExpression rx("^[\\w.%+-]+@[\\w.-]+\\.[A-Za-z]{2,}$");
    if(!rx.match(email).hasMatch())
    {
        showTipWnd("Incorrect email format");
        return FAIL;
    }
    rx = QRegularExpression("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@#$%^&+=!])(?=.*[^\\s]).{6,}$");
    if(!rx.match(password).hasMatch())
    {
        showTipWnd("Incorrect password format");
        return FAIL;
    }

    QSqlQuery query;
    bool result = query.exec(QString("select *from AccountInfo where email='%1'").arg(email));
    if (result)
    {
        while (query.next())
        {
            QString queryPassword = query.value("password").toString();
            if (queryPassword == password)
            {
                return SUCCESS;
            }
            else
            {
                showTipWnd("password error");
                return FAIL;
            }
        }
        showTipWnd("Invalid email");
        return FAIL;

    }
    else
    {
        showTipWnd("Invalid email");
        return FAIL;
    }
}


void LoginView::initPassword()
{
    QSettings *remberPassword = new QSettings("useinfo", QSettings::IniFormat);
    QString strUser = remberPassword->value("email").toString();
    QString strPassword = remberPassword->value("password").toString();
    delete remberPassword;
    if (strUser == "" || strPassword == "")
    {
        ui->rembpwd->setChecked(false);
    }
    else
    {
        ui->rembpwd->setChecked(true);
        ui->emailEdit->setText(strUser);
        ui->passwordEdit->setText(strPassword);
    }
}

void LoginView::showTipWnd(QString text)
{
    if(!tip)
    {
        tip = new QLabel(text,this);
        tip->setGeometry(420,230,251,60);
        tip->setAlignment(Qt::AlignCenter);
        tip->setStyleSheet("border-radius:13px;background-color: rgba(6, 6, 6, 166);color: rgb(255, 255, 255);");
        QFont font("Arial", 13);
        tip->setFont(font);
    }
    else
    {
        tip->setText(text);
    }

    tip->move(this->width()/2-tip->width()/2,this->height()/2-tip->height()/2);
    tip->show();

    timer->start(1500);

}

void LoginView::rememberPassword()
{
    bool value = ui->rembpwd->isChecked();
    QString userName = ui->emailEdit->text();
    QString password = ui->passwordEdit->text();
    QSettings *remberPassword = new QSettings("useinfo", QSettings::IniFormat);
    if (value || userName =="" || password == "")
    {
        remberPassword->setValue("email", userName);
        remberPassword->setValue("password", password);

    }
    else
    {
        remberPassword->setValue("email", "");
        remberPassword->setValue("password", "");
    }
    delete remberPassword;
}

void LoginView::loginSystem()
{
    qDebug() << "clicked";
    int result = getUserPassword(); //用户名密码是否正确
    if (result == SUCCESS)
    {

        rememberPassword();
        this->close();
        MainSystem *mainWnd = new MainSystem();
        mainWnd->show();
    }

}

void LoginView::openSignUpWnd()
{
    this->close();
    SignUpWnd* signUp = new SignUpWnd();
    signUp->show();

}

void LoginView::openForgotPsdWnd()
{
    this->close();
    ForgotPassword* forgotPsd = new ForgotPassword;
    forgotPsd->show();
}
