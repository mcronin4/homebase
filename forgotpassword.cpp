#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include "loginview.h"
#include "datamanage.h"
#include <QRegularExpression>

ForgotPassword::ForgotPassword(QWidget *parent) :
    mouseMoveEventWindows(parent),
    ui(new Ui::ForgotPassword)
    , tip(nullptr)
    , timer(nullptr)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->commandLinkButton,&QCommandLinkButton::clicked,this,&ForgotPassword::openLoginWnd);
    connect(ui->getBtn,&QPushButton::clicked,this,&ForgotPassword::getPassword);
    connect(ui->closedBtn,&QPushButton::clicked,this,[this]{
        this->close();
    });
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[&]{
        if(tip)
            tip->hide();
    });
}

ForgotPassword::~ForgotPassword()
{
    delete ui;
}

void ForgotPassword::openLoginWnd()
{
    LoginView* loginWnd = new LoginView;
    loginWnd->show();
    this->close();
}

QWidget *ForgotPassword::getDragnWidget()
{
    return ui->widget;
}

void ForgotPassword::getPassword()
{
    QString email = ui->emailEdit->text();
    QString resetcode = ui->safeCodeEdit->text();

    if(email == "" || resetcode == "")
    {
        showTipWnd("Input cannot be null");
        return;
    }
    QRegularExpression rx("^[\\w.%+-]+@[\\w.-]+\\.[A-Za-z]{2,}$");
    if(!rx.match(email).hasMatch())
    {
        showTipWnd("invalid email");
        return;
    }

    QSqlQuery query;
    bool result = query.exec(QString("select *from AccountInfo where email='%1'").arg(email));
    if (result)
    {
        while (query.next())
        {
            QString queryCode = query.value("resetcode").toString();
            if (queryCode == resetcode)
            {
                setShowPassword(query.value("password").toString());
                return;
            }
            else
            {
                showTipWnd("Invalid resetcode");
                return;
            }
        }
    }
    else
    {
        showTipWnd("Invalid email");
        return;
    }
}

void ForgotPassword::showTipWnd(QString text)
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

void ForgotPassword::setShowPassword(QString str)
{
    ui->passwordLab->setText("Password: " + str);
}
