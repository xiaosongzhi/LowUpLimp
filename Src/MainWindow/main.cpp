
#include <QApplication>
#include "cdatabaseinterface.h"
#include "mainwindow.h"
#include <QDebug>
//#include "loginwidget.h"
#include "cmainwindow.h"
#include "gamedisplaypage.h"

int main(int argc, char *argv[])
{
//    qputenv("QT_IM_MODULE",QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    if(!CDatabaseInterface::getInstance()->openDB("./DependFile/DBFile/UpLow.db","QSQLITE"))
        qDebug()<<"UpLow.db open failed!";
    MainWindow w;
    w.show();
    return a.exec();
}
