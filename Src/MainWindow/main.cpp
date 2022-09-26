//#include "mainwindow.h"
#include <QApplication>
#include "cdatabaseinterface.h"
//#include "settingwidget.h"
#include <QDebug>
//#include "loginwidget.h"
#include "usermanager.h"
//#include "cmainwindow.h"
//#include "fessetting.h"
//#include "armorleg.h"
#include "channeldialog.h"
#include "gamedisplaypage.h"
int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE",QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    if(!CDatabaseInterface::getInstance()->openDB("./DependFile/DBFile/UpLow.db","QSQLITE"))
        qDebug()<<"UpLow.db open failed!";
    ChannelDialog w;
    w.show();
//    UserManager w;
//    w.show();
    return a.exec();
}
