#include <QApplication>
#include "cdatabaseinterface.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
//#include "loginwidget.h"
#include "cmainwindow.h"
#include "readconfig.h"
#include "loginwidget.h"
#include "gamecontrol.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //数据库读取
    if(!CDatabaseInterface::getInstance()->openDB("./DependFile/DBFile/UpLow.db","QSQLITE"))
        qDebug()<<"UpLow.db open failed!";
    //配置文件读取
    if(!ReadConfig::getInstance()->readConfigFile())
    {
        qDebug()<<"配置文件读取失败";
        return -1;
    }

    //读取游戏配置文件
    GameControl::getInstance()->readGameConfigMsg();

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

    LoginWidget login;
    CMainWindow w;
    QObject::connect(&w,SIGNAL(signalShowCompleted()),&login,SLOT(slotShowCompleted()));
    login.exec();
    w.show();

    return a.exec();
}
