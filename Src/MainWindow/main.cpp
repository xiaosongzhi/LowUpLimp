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
#include <QSharedMemory>
#include <QMutex>
#include <QFile>
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();
    QString text;
    switch(type)
    {
        case QtDebugMsg:
            text = QString("Debug:");
            break;
        case QtWarningMsg:
            text = QString("Warning:");
            break;
        case QtCriticalMsg:
            text = QString("Critical:");
            break;
        case QtFatalMsg:
            text = QString("Fatal:");
    }
    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();
    mutex.unlock();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    qInstallMessageHandler(outputMessage);
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

    QSharedMemory sharedMemory;
    sharedMemory.setKey("main_Window");
    if(sharedMemory.attach())
    {
        QMessageBox::warning(NULL, "Warning", ("不可重复开启进程"));
        return 0;
    }

    LoginWidget login;
    CMainWindow w;
    if(sharedMemory.create(1))
    {
        QObject::connect(&w,SIGNAL(signalShowCompleted()),&login,SLOT(slotShowCompleted()));
        login.exec();
        w.show();
    }

    return a.exec();

}
