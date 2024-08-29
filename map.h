#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QBuffer>
#include <QFile>
#include <QQuickItem>
#include <QVariant>
#include "mousemoveeventwindows.h"

namespace Ui {
class Map;
}

class Map : public mouseMoveEventWindows
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();
    QWidget *getDragnWidget();
    //void createMapWidget();


public slots:
    void openLoginWnd();
    void openMainSystem();
    //maybe implement this later
    void openChat();
    //QString createMapIO();
    //void changeCoord();

private:
    Ui::Map *ui;
    //QWebEngineView *mapWidget;
    //double lat;
    //double lon;
    //int zoom;
signals:
    void setCenter(QVariant, QVariant);
    void addMarker(QVariant, QVariant);
};

#endif // MAP_H
