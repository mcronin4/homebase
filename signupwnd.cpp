#include "signupwnd.h"
#include "ui_signupwnd.h"
#include "loginview.h"
#include "datamanage.h"
#include <QRegularExpression>

SignUpWnd::SignUpWnd(QWidget *parent) :
    mouseMoveEventWindows(parent),
    ui(new Ui::SignUpWnd)
    , tip(nullptr)
    , timer(nullptr)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->commandLinkButton,&QCommandLinkButton::clicked,this,&SignUpWnd::openLoginWnd);
    connect(ui->signupBtn,&QPushButton::clicked,this,&SignUpWnd::signupProcess);
    connect(ui->closedBtn,&QPushButton::clicked,this,[this]{
        this->close();
    });
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[&]{
        if(tip)
            tip->hide();
    });
}

SignUpWnd::~SignUpWnd()
{
    delete ui;
}

void SignUpWnd::openLoginWnd()
{
    LoginView* loginWnd = new LoginView;
    loginWnd->show();
    this->close();
}

QWidget *SignUpWnd::getDragnWidget()
{
    return ui->widget;
}

void SignUpWnd::signupProcess()
{
    QString firstName = ui->firstNameEdit->text();
    QString lastName = ui->lastNameEdit->text();
    QString email = ui->emailEdit->text();
    QString phone = ui->phoneNumberEdit->text();
    QString userName = ui->userNameEdit->text();
    QString password = ui->passwordEdit->text();
    QString resetcode = ui->safeCodeEdit->text();

    if(firstName == "" || lastName=="" || email == "" || phone == "" || userName == "" || password =="" || resetcode == "")
    {
        showTipWnd("Input cannot be null");
        return;
    }
    QRegularExpression rx("^[\\w.%+-]+@[\\w.-]+\\.[A-Za-z]{2,}$");
    if(!rx.match(email).hasMatch())
    {
        showTipWnd("Incorrect email format");
        return;
    }
    rx = QRegularExpression("^\\d+$");
    if(!rx.match(phone).hasMatch())
    {
        showTipWnd("Incorrect phone format");
        return;
    }

    rx = QRegularExpression("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@#$%^&+=!])(?=.*[^\\s]).{6,}$");
    if(!rx.match(password).hasMatch())
    {
        showTipWnd("Incorrect password format");
        return;
    }
    if(!isExisted("email",email))
    {
        return;
    }
    if(!isExisted("username",userName))
    {
        return;
    }
    if(DataManage::getInstance()->addRecordDB(userName,password,resetcode,firstName,lastName,email,phone))
    {
        showTipWnd("signup success");
    }
    else
        showTipWnd("signup fail");
}

bool SignUpWnd::isExisted(QString nType, const QString &value)
{
    QSqlQuery query;
    query.exec(QString("SELECT * from AccountInfo WHERE " + nType + " = '%1'").arg(value));
    if(!query.next())
    {
        return true;
    }
    else
    {
        showTipWnd("The " + nType  + " exists");
        return false;
    }
}


void SignUpWnd::showTipWnd(QString text)
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
