#include "gamecontainer.h"
#include "ui_gamecontainer.h"
#include <QProcess>
#include <QDebug>
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
    process->start(path);
}
