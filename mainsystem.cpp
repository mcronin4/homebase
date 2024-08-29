#include "mainsystem.h"
#include "ui_browseview.h"
#include "ui_mainsystem.h"
#include "loginview.h"
#include "map.h"
#include "browseview.h"
#include "chatview.h"
MainSystem::MainSystem(QWidget *parent) :
    mouseMoveEventWindows(parent),
    ui(new Ui::MainSystem)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->logoutBtn,&QPushButton::clicked,this,&MainSystem::openLoginWnd);
    connect(ui->closedBtn,&QPushButton::clicked,this,[this]{
        this->close();
    });
    //change to browse house page later
    connect(ui->browseBtn,&QPushButton::clicked,this,&MainSystem::openBrowseWnd);
    //change to map page later
    connect(ui->mapBtn,&QPushButton::clicked,this,&MainSystem::openMapWnd);
    //change to page later
    connect(ui->chatBtn,&QPushButton::clicked,this,&MainSystem::openChatWnd);
}
void MainSystem::openLoginWnd()
{
    LoginView* loginWnd = new LoginView;
    loginWnd->show();
    this->close();
}

void MainSystem::openChatWnd()
{
    ChatView* chatWnd = new ChatView;
    chatWnd->show();
    this->close();
}

void MainSystem::openBrowseWnd()
{
    BrowseView* browseWnd = new BrowseView;
    browseWnd->show();
    this->close();
}


void MainSystem::openMapWnd()
{
    Map* mapWnd = new Map;
    mapWnd->setAttribute(Qt::WA_DeleteOnClose);
    mapWnd->show();
    this->close();

}

QWidget *MainSystem::getDragnWidget()
{
    return ui->widget;
}

MainSystem::~MainSystem()
{
    delete ui;
}
