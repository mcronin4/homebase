#include "map.h"
#include "ui_map.h"
#include "mainsystem.h"
#include "loginview.h"

Map::Map(QWidget *parent) :
    mouseMoveEventWindows(parent),
    ui(new Ui::Map)//,
    //mapWidget(new QWebEngineView(this))
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();
    auto obj = ui->quickWidget->rootObject();
    connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
    connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));
    emit setCenter(44.2333,-76.5000);
    emit addMarker(46.550684,-119.5000);
    emit addMarker(42.450684,-89.5000);
    emit addMarker(45.450684,-90.5000);
    emit addMarker(45.450684,-76.5000);
    //mapWidget->setGeometry(126,110,1085,530);
    ////mapWidget->setParent(ui->mapView);

    //mapWidget->setHtml(html);
    //mapWidget->show();

    //logout and close buttons here
    connect(ui->logoutBtn,&QPushButton::clicked,this,&Map::openLoginWnd);
    connect(ui->closedBtn,&QPushButton::clicked,this,[this]{
        this->close();
    });
    //connect action to button here
    connect(ui->backButton,&QPushButton::clicked,this,&Map::openMainSystem);

    //this->createMapWidget();

}

/*
void Map::createMapWidget() {
    mapWidget->setGeometry(126,110,1085,530);
    QString url = QString("https://www.openstreetmap.org/export/embed.html?bbox=%1,%2,%3,%4&layer=mapnik").arg(-76.5000 - 0.01).arg(44.2333 - 0.01).arg(-76.5000 + 0.01).arg(44.2333 + 0.01);
    mapWidget->setUrl(QUrl(url));
    //QString html = createMapIO();
    //mapWidget->setHtml(html);
    mapWidget->show();
}
*/
/*
QString Map::createMapIO() {
    QString html = QString("<!DOCTYPE html>"
                           "<html>"
                           "<head>"
                           "<title>OpenStreetMap</title>"
                           "<meta charset='utf-8'/>"
                           "<style>"
                           "body, html, #map {"
                           "   height: 100%;"
                           "   margin: 0;"
                           "   padding: 0;"
                           "}"
                           "</style>"
                           "<script src='https://www.openlayers.org/api/OpenLayers.js'></script>"
                           "</head>"
                           "<body>"
                           "<div id='map' style='width: 100%; height: 100%;'></div>"
                           "<script>"
                           "// Initialize map"
                           "var map = new OpenLayers.Map('map');"
                           "var mapnik = new OpenLayers.Layer.OSM();"
                           "map.addLayer(mapnik);"
                           "// Set map center and zoom level"
                           "map.setCenter(new OpenLayers.LonLat(44.2333,-76.5000), 10);"
                           "// Add markers or other interactive features as needed"
                           "</script>"
                           "</body>"
                           "</html>");
    return html;
}
*/

//implmentation openLoginWnd()
void Map::openLoginWnd(){
    LoginView* loginWnd = new LoginView;
    loginWnd->show();
    this->close();
}

//open MainSytem (homepage implementation)
void Map::openMainSystem() {
    MainSystem * mainSystemWnd = new MainSystem;
    mainSystemWnd->show();
    this->close();
}

//open chat can be implemented later on (once chat.cpp/h is included in this project)
void Map::openChat() {
    //TODO
}

//void changeCoord() {
    //TODO
//}

QWidget *Map::getDragnWidget()
{
    return ui->widget;
}

//destructr
Map::~Map()
{
    //delete mapWidget;
    //mapWidget=nullptr;
    delete ui;
}
