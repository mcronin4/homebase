#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include <QWidget>
#include "mousemoveeventwindows.h"

namespace Ui {
    class MainSystem;
}

class MainSystem : public mouseMoveEventWindows
{
    Q_OBJECT

public:
    explicit MainSystem(QWidget *parent = nullptr);
    ~MainSystem();
    QWidget *getDragnWidget();

public slots:
    void openLoginWnd();
    void openBrowseWnd();
    void openChatWnd();
    void openMapWnd();
private:
    Ui::MainSystem *ui;
};

#endif // MAINSYSTEM_H
