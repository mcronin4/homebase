#ifndef BROWSEVIEW_H
#define BROWSEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include "mousemoveeventwindows.h"
namespace Ui {
class BrowseView;
}

class BrowseView : public mouseMoveEventWindows
{
    Q_OBJECT

public:
    explicit BrowseView(QWidget *parent = nullptr);
    ~BrowseView();

    QWidget *getDragnWidget();

private:
    Ui::BrowseView *ui;
    QLabel* tip;
    QTimer* timer;
    //QSqlQueryModel *model;
    QStandardItemModel *model;
    void setupModel();
    void addSampleHouse(const QString &address, int bathrooms, int bedrooms, int rent, const QString &landlord);

public slots:
    void openLoginWnd();
    void openBrowseWnd();
    void openHomeWnd();
    void openMapWnd();
    void openChatWnd();
};

#endif // BROWSEVIEW_H

