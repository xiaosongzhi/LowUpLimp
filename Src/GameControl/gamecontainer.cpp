#include "gamecontainer.h"
#include "ui_gamecontainer.h"
#include <QProcess>
#include <QShowEvent>
#include <QDebug>
#include "dataformate.h"
#include <QTimer>
#include <windows.h>
#include <QHBoxLayout>
GameContainer::GameContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameContainer),
    process(nullptr)
{
    ui->setupUi(this);
    initProcess();
}

GameContainer::~GameContainer()
{
    if(process)
        delete process;
    delete ui;
}

void GameContainer::initProcess()
{
    process = new QProcess();
    connect(process,&QProcess::errorOccurred,[=](QProcess::ProcessError error){qDebug()<<error;});
        connect(process,QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished),[this]
                (int exitCode,QProcess::ExitStatus exitStatus){
            m_exitCode = exitCode;
            m_exitStatus = exitStatus;
            qDebug()<<"m_exitCode"<<m_exitCode<<"m_exitStatus"<<m_exitStatus;
        });
}

void GameContainer::startGame(QString path)
{

}

void GameContainer::showEvent(QShowEvent *event)
{
//    qDebug()<<"showEvent";
//    QString path = "./GameDemo/game801/game801/MultiplayerBicycleRace.exe";

//    process->start(path);
//    Sleep(10);
//    WId hwnd = 0;

//    do{
//        QEventLoop loop;
//        //1ms之后退出
//        QTimer::singleShot(1,&loop,SLOT(quit()));
//        hwnd = (WId)FindWindow(L"UnityWndClass",L"DuoRenQiChe2");
//    }while(hwnd == 0);
//    m_window = QWindow::fromWinId(hwnd);
//    QWidget *container = createWindowContainer(m_window,this);

//    QHBoxLayout *hLayout = new QHBoxLayout(this);
//    hLayout->setMargin(0);
//    hLayout->addWidget(container);
//    this->setLayout(hLayout);
}
