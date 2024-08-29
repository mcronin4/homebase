QT       += core gui sql quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    browseview.cpp \
    datamanage.cpp \
    forgotpassword.cpp \
    loginview.cpp \
    main.cpp \
    mainsystem.cpp \
    mainwindow.cpp \
    map.cpp \
    chatview.cpp \
    mousemoveeventwindows.cpp \
    signupwnd.cpp

HEADERS += \
    browseview.h \
    datamanage.h \
    forgotpassword.h \
    loginview.h \
    mainsystem.h \
    map.h \
    chatview.h \
    mainwindow.h \
    mousemoveeventwindows.h \
    signupwnd.h

FORMS += \
    browseview.ui \
    forgotpassword.ui \
    loginview.ui \
    map.ui \
    chatview.ui \
    mainsystem.ui \
    mainwindow.ui \
    signupwnd.ui

TRANSLATIONS += \
    HomeBase_fr_CA.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc \
    qml.qrc
