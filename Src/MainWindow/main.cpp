#include <QApplication>
#include "cdatabaseinterface.h"
#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
//#include "loginwidget.h"
#include "cmainwindow.h"
#include "gamedisplaypage.h"

#include "loginwidget.h"

int main(int argc, char *argv[])
{
    //    qputenv("QT_IM_MODULE",QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    if(!CDatabaseInterface::getInstance()->openDB("./DependFile/DBFile/UpLow.db","QSQLITE"))
        qDebug()<<"UpLow.db open failed!";

    //设置全局样式表
    QFile file("./DependFile/QSS/app.txt");
    if(file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
    else
    {
        QMessageBox::warning(NULL, "warning", "totalqss Open failed", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

    CMainWindow w;
    w.show();
    LoginWidget login;
    login.show();

    return a.exec();
}
