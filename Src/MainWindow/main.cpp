//#include "mainwindow.h"
#include <QApplication>
#include "cdatabaseinterface.h"
#include <QDebug>
#include "loginwidget.h"
//#include "usermanager.h"
#include "cmainwindow.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE",QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    if(!CDatabaseInterface::getInstance()->openDB("./DependFile/DBFile/UpLow.db","QSQLITE"))
        qDebug()<<"UpLow.db open failed!";
    CMainWindow w;
    w.show();
//    UserManager w;
//    w.show();
    return a.exec();
}
