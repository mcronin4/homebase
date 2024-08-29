#include <QStandardItemModel>
#include "browseview.h"
#include "ui_browseview.h"
#include "mainsystem.h"
#include "loginview.h"
#include "map.h"
#include "chatview.h"
#include "datamanage.h"

BrowseView::BrowseView(QWidget *parent) :
    mouseMoveEventWindows(parent),
    ui(new Ui::BrowseView),
    model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->logoutBtn,&QPushButton::clicked,this,&BrowseView::openLoginWnd);
    connect(ui->closedBtn,&QPushButton::clicked,this,[this]{
        this->close();
    });
    //change to browse house page later
    connect(ui->backBtn,&QPushButton::clicked,this,&BrowseView::openHomeWnd);
    //change to map page later
    connect(ui->mapBtn,&QPushButton::clicked,this,&BrowseView::openMapWnd);
    //change to page later
    connect(ui->chatBtn,&QPushButton::clicked,this,&BrowseView::openChatWnd); //CHANGE THIS TO CHAT

    //QStandardItemModel *model = new QStandardItemModel(this);
    setupModel();
    ui->tableView->setModel(model);
}

void BrowseView::setupModel() {
    model->setColumnCount(5);
    model->setHorizontalHeaderLabels({"Address", "Bathrooms", "Bedrooms", "Rent", "Landlord"});
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QFont headerFont("Arial", 15);
    headerFont.setBold(true);
    ui->tableView->horizontalHeader()->setFont(headerFont);
    ui->tableView->verticalHeader()->setFont(headerFont);

    addSampleHouse("123 Main St", 1, 2, 800, "John Doe");
    addSampleHouse("456 Redwood St", 2, 3, 950, "Jane Smith");
    addSampleHouse("789 Maple Ave", 2, 4, 1050, "Alice Johnson");
    addSampleHouse("321 Oak Ln", 1, 3, 900, "James Anderson");
    addSampleHouse("654 Pine Dr", 2, 5, 1100, "Karen White");
    addSampleHouse("987 Cedar Blvd", 3, 4, 1200, "Robert Davis");
    addSampleHouse("246 Willow St", 1, 2, 750, "Jennifer Wilson");
    addSampleHouse("135 Spruce Ct", 2, 3, 850, "William Moore");
    addSampleHouse("864 Birch Rd", 1, 2, 1300, "Patricia Taylor");
}

void BrowseView::addSampleHouse(const QString &address, int bathrooms, int bedrooms, int rent, const QString &landlord) {
    QList<QStandardItem *> row;

    QStandardItem *addressItem = new QStandardItem(address);
    addressItem->setFont(QFont("Arial", 15));
    addressItem->setForeground(QBrush(Qt::black));
    row << addressItem;

    QStandardItem *bathroomsItem = new QStandardItem(QString::number(bathrooms));
    bathroomsItem->setFont(QFont("Arial", 15));
    bathroomsItem->setForeground(QBrush(Qt::black));
    row << bathroomsItem;

    QStandardItem *bedroomsItem = new QStandardItem(QString::number(bedrooms));
    bedroomsItem->setFont(QFont("Arial", 15));
    bedroomsItem->setForeground(QBrush(Qt::black));
    row << bedroomsItem;

    QStandardItem *rentItem = new QStandardItem(QString::number(rent));
    rentItem->setFont(QFont("Arial", 15));
    rentItem->setForeground(QBrush(Qt::black));
    row << rentItem;

    QStandardItem *landlordItem = new QStandardItem(landlord);
    landlordItem->setFont(QFont("Arial", 15));
    landlordItem->setForeground(QBrush(Qt::black));
    row << landlordItem;

    model->appendRow(row);
}

void BrowseView::openLoginWnd()
{
    LoginView* loginWnd = new LoginView;
    loginWnd->show();
    this->close();
}

//this function is not needed
void BrowseView::openBrowseWnd()
{
    //BrowseView* browseWnd = new BrowseView;
    //browseWnd->show();
    //this->close();
}

void BrowseView::openHomeWnd()
{
    MainSystem * homeWnd = new MainSystem;
    homeWnd->show();
    this->close();
}

void BrowseView::openMapWnd()
{
    Map * mapWnd = new Map;
    mapWnd->show();
    this->close();
}

void BrowseView::openChatWnd()
{
    ChatView* chatWnd = new ChatView;
    chatWnd->show();
    this->close();
}

BrowseView::~BrowseView()
{
    delete ui;
}

QWidget *BrowseView::getDragnWidget()
{
    return ui->widget;
}
