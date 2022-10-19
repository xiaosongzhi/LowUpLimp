#include <QApplication>
#include "cdatabaseinterface.h"
#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
//#include "loginwidget.h"
#include "cmainwindow.h"
#include "readconfig.h"
#include "ccommunicateapi.h"
#include "loginwidget.h"

int main(int argc, char *argv[])
{

    //    qputenv("QT_IM_MODULE",QByteArray("qtvirtualkeyboard"));
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

    ST_BicycleParam st_bicycleParam;
    st_bicycleParam.controlState = 1;
    st_bicycleParam.bodyPart =1;
    st_bicycleParam.trainMode = 9;
    st_bicycleParam.spasmSwitch = 1;
    st_bicycleParam.spasmLevel = 2;
    st_bicycleParam.configPower = 0;
    st_bicycleParam.switchDirectonTime = 0;
    st_bicycleParam.phaseValue = 9;
    st_bicycleParam.direction = 1;
    st_bicycleParam.speed = 5;
    st_bicycleParam.resistance = 2;
    st_bicycleParam.spasmType = 1;
    CCommunicateAPI::getInstance()->sendBicycleParam(st_bicycleParam);

    return a.exec();
}
