QT       += core gui sql printsupport quickwidgets network serialport xml multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#Qt5.15.2 mingw64
#指定UI文件生成的位置
UI_DIR = ./UI

MOC_DIR = tmp/moc

OBJECTS_DIR = tmp/obj

RCC_DIR = tmp/rcc

CONFIG += c++17
DEFINES += UNIFORMLY   HEARTBEAT #上下肢统一,是否开启心跳
#static{
#QTPLUGIN += qtvirtualkeyboardplugin
#QT += svg
#}
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
               $$PWD/Src/Communication \
               $$PWD/Src/CustomWidget \
               $$PWD/Src/PopDialog \
               $$PWD/Src/GameControl \
               $$PWD/Src/ICEModule
SOURCES += \
    Src/Communication/ccommunicateapi.cpp \
    Src/Communication/ccommunicationinterface.cpp \
    Src/Communication/cserialportinterface.cpp \
    Src/Communication/ctcpsocketinterface.cpp \
    Src/Communication/cudpinterface.cpp \
    Src/Communication/globalqueue.cpp \
    Src/Communication/readconfig.cpp \
    Src/CustomWidget/fesparambtn.cpp \
    Src/CustomWidget/musclebutton.cpp \
    Src/DataBaseControl/cdatabaseinterface.cpp \
    Src/DataBaseControl/mysqldatabase.cpp \
    Src/DataFormate/dataformate.cpp \
    Src/DataFormate/dbforrmate.cpp \
    Src/GameControl/gamecontainer.cpp \
    Src/GameControl/gamecontrol.cpp \
    Src/GameControl/gamedisplaypage.cpp \
    Src/ICEModule/icemodule.cpp \
    Src/MainWindow/cmainwindow.cpp \
    Src/MainWindow/loginwidget.cpp \
    Src/MainWindow/main.cpp \
    Src/MainWindow/mainwindow.cpp \
    Src/MainWindow/mainwindowpagecontrol.cpp \
    Src/MainWindow/titlewidget.cpp \
    Src/PopDialog/advanceddialog.cpp \
    Src/PopDialog/deleteuserdialog.cpp \
    Src/PopDialog/emergencystopdialog.cpp \
    Src/PopDialog/festipsdialog.cpp \
    Src/PopDialog/paramtipsdialog.cpp \
    Src/PopDialog/passworddialog.cpp \
    Src/PopDialog/quitgamedialog.cpp \
    Src/PopDialog/selectuserdialog.cpp \
    Src/PopDialog/spasmtipsdialog.cpp \
    Src/Report/trainreport.cpp \
    Src/Setting/settingwidget.cpp \
    Src/TrainManager/armorleg.cpp \
#    Src/TrainManager/fesparamset.cpp \
    Src/TrainManager/fessetting.cpp \
    Src/TrainManager/trainmanager.cpp \
    Src/TrainRecord/trainrecord.cpp \
    Src/UserManager/currentuserdata.cpp \
    Src/UserManager/userdialog.cpp \
    Src/UserManager/usermanager.cpp \
    Src/PopDialog/festotalparamdialog.cpp \
    Src/PopDialog/channeldialog.cpp

HEADERS += \
    Src/Communication/ccommunicateapi.h \
    Src/Communication/ccommunicationinterface.h \
    Src/Communication/cserialportinterface.h \
    Src/Communication/ctcpsocketinterface.h \
    Src/Communication/cudpinterface.h \
    Src/Communication/globalqueue.h \
    Src/Communication/readconfig.h \
    Src/CustomWidget/fesparambtn.h \
    Src/CustomWidget/musclebutton.h \
    Src/DataBaseControl/cdatabaseinterface.h \
    Src/DataBaseControl/mysqldatabase.h \
    Src/DataFormate/dataformate.h \
    Src/DataFormate/dbforrmate.h \
    Src/GameControl/gamecontainer.h \
    Src/GameControl/gamecontrol.h \
    Src/GameControl/gamedisplaypage.h \
    Src/ICEModule/icemodule.h \
    Src/MainWindow/cmainwindow.h \
    Src/MainWindow/loginwidget.h \
    Src/MainWindow/mainwindow.h \
    Src/MainWindow/mainwindowpagecontrol.h \
    Src/MainWindow/titlewidget.h \
    Src/PopDialog/advanceddialog.h \
    Src/PopDialog/deleteuserdialog.h \
    Src/PopDialog/emergencystopdialog.h \
    Src/PopDialog/festipsdialog.h \
    Src/PopDialog/paramtipsdialog.h \
    Src/PopDialog/passworddialog.h \
    Src/PopDialog/quitgamedialog.h \
    Src/PopDialog/selectuserdialog.h \
    Src/PopDialog/spasmtipsdialog.h \
    Src/Report/trainreport.h \
    Src/Setting/settingwidget.h \
    Src/TrainManager/armorleg.h \
#    Src/TrainManager/fesparamset.h \
    Src/TrainManager/fessetting.h \
    Src/TrainManager/trainmanager.h \
    Src/TrainRecord/trainrecord.h \
    Src/UserManager/currentuserdata.h \
    Src/UserManager/userdialog.h \
    Src/UserManager/usermanager.h \
    Src/PopDialog/festotalparamdialog.h \
    Src/PopDialog/channeldialog.h

FORMS += \
    Src/CustomWidget/fesparambtn.ui \
    Src/CustomWidget/musclebutton.ui \
    Src/GameControl/gamecontainer.ui \
    Src/GameControl/gamedisplaypage.ui \
    Src/MainWindow/cmainwindow.ui \
    Src/MainWindow/loginwidget.ui \
    Src/MainWindow/mainwindow.ui \
    Src/MainWindow/titlewidget.ui \
    Src/PopDialog/advanceddialog.ui \
    Src/PopDialog/deleteuserdialog.ui \
    Src/PopDialog/emergencystopdialog.ui \
    Src/PopDialog/festipsdialog.ui \
    Src/PopDialog/paramtipsdialog.ui \
    Src/PopDialog/passworddialog.ui \
    Src/PopDialog/quitgamedialog.ui \
    Src/PopDialog/selectuserdialog.ui \
    Src/PopDialog/spasmtipsdialog.ui \
    Src/Report/trainreport.ui \
    Src/Setting/settingwidget.ui \
    Src/TrainManager/armorleg.ui \
#    Src/TrainManager/fesparamset.ui \
    Src/TrainManager/fessetting.ui \
    Src/TrainManager/trainmanager.ui \
    Src/TrainRecord/trainrecord.ui \
    Src/UserManager/userdialog.ui \
    Src/UserManager/usermanager.ui \
    Src/PopDialog/festotalparamdialog.ui \
    Src/PopDialog/channeldialog.ui

LIBS+=-lwlanapi

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

RC_ICONS = logo.ico
