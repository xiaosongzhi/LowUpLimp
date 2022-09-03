QT       += core gui sql printsupport quickwidgets network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#指定UI文件生成的位置
UI_DIR = ./UI

CONFIG += c++17

static{
QTPLUGIN += qtvirtualkeyboardplugin
QT += svg
}
#QMAKE_MSC_VER = 2015
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/Src/MainWindow \
               $$PWD/Src/DataBaseControl \
               $$PWD/Src/DataFormate \
               $$PWD/Src/UserManager \
               $$PWD/Src/TrainRecord \
               $$PWD/Src/Report \
               $$PWD/Src/TrainManager \
               $$PWD/Src/Setting \
               $$PWD/Src/Communication
SOURCES += \
    Src/Communication/ccommunicateapi.cpp \
    Src/Communication/ccommunicationinterface.cpp \
    Src/Communication/cserialportinterface.cpp \
    Src/Communication/ctcpsocketinterface.cpp \
    Src/Communication/cudpinterface.cpp \
    Src/Communication/globalqueue.cpp \
    Src/Communication/readconfig.cpp \
    Src/DataBaseControl/cdatabaseinterface.cpp \
    Src/DataBaseControl/mysqldatabase.cpp \
    Src/DataFormate/dbforrmate.cpp \
    Src/MainWindow/cmainwindow.cpp \
    Src/MainWindow/loginwidget.cpp \
    Src/MainWindow/main.cpp \
    Src/MainWindow/mainwindow.cpp \
    Src/MainWindow/mainwindowpagecontrol.cpp \
    Src/MainWindow/titlewidget.cpp \
    Src/Report/trainreport.cpp \
    Src/Setting/settingwidget.cpp \
    Src/TrainManager/trainmanager.cpp \
    Src/TrainRecord/trainrecord.cpp \
    Src/UserManager/currentuserdata.cpp \
    Src/UserManager/userdialog.cpp \
    Src/UserManager/usermanager.cpp

HEADERS += \
    Src/Communication/ccommunicateapi.h \
    Src/Communication/ccommunicationinterface.h \
    Src/Communication/cserialportinterface.h \
    Src/Communication/ctcpsocketinterface.h \
    Src/Communication/cudpinterface.h \
    Src/Communication/globalqueue.h \
    Src/Communication/readconfig.h \
    Src/DataBaseControl/cdatabaseinterface.h \
    Src/DataBaseControl/mysqldatabase.h \
    Src/DataFormate/dataformate.h \
    Src/DataFormate/dbforrmate.h \
    Src/MainWindow/cmainwindow.h \
    Src/MainWindow/loginwidget.h \
    Src/MainWindow/mainwindow.h \
    Src/MainWindow/mainwindowpagecontrol.h \
    Src/MainWindow/titlewidget.h \
    Src/Report/trainreport.h \
    Src/Setting/settingwidget.h \
    Src/TrainManager/trainmanager.h \
    Src/TrainRecord/trainrecord.h \
    Src/UserManager/currentuserdata.h \
    Src/UserManager/userdialog.h \
    Src/UserManager/usermanager.h

FORMS += \
    Src/MainWindow/cmainwindow.ui \
    Src/MainWindow/loginwidget.ui \
    Src/MainWindow/mainwindow.ui \
    Src/MainWindow/titlewidget.ui \
    Src/Report/trainreport.ui \
    Src/Setting/settingwidget.ui \
    Src/TrainManager/trainmanager.ui \
    Src/TrainRecord/trainrecord.ui \
    Src/UserManager/userdialog.ui \
    Src/UserManager/usermanager.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
