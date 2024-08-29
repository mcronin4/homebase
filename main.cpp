#include "mainwindow.h"
#include "loginview.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "datamanage.h"
void init();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    init();
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "HomeBase_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    //MainWindow *w = new MainWindow;
    //w->show();

    LoginView *w = new LoginView;
    w->show();
    return a.exec();
}

void init()
{
    DataManage::getInstance()->init();
}
