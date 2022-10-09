#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include "mainwindowpagecontrol.h"
#include "currentuserdata.h"
#include <QDebug>
#include <QTimer>
#include <windows.h>
#include <QHBoxLayout>


CMainWindow::CMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMainWindow),
    m_gameDisplayPage(NULL)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    qRegisterMetaType<E_PAGENAME>("E_PAGENAME");
    connect(MainWindowPageControl::getInstance(),SIGNAL(signalSwitchPage(E_PAGENAME)),this,SLOT(slotSwitchPage(E_PAGENAME)));
    connect(CurrentUserData::getInstace(),SIGNAL(signalUserChanged()),this,SLOT(slotCurrentUserChanged()));
    //默认为主界面
//    setAttribute(Qt::WA_DeleteOnClose,false);
    ui->stackedWidget->setCurrentIndex(0);
    m_gameDisplayPage = new GameDisplayPage();
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::switchPage(E_PAGENAME E_Page)
{
    switch(E_Page)
    {
    case MainPage_E:
        ui->stackedWidget->setCurrentWidget(ui->Main_Page);
        break;
    case TrainingPage_E://游戏训练界面
        ui->stackedWidget->setCurrentWidget(ui->game_Page);
        m_gameDisplayPage->move(0,0);
//        m_gameDisplayPage->show();
        QTimer::singleShot(10000,this,SLOT(slot_Timerout()));//同上，就是参数不同
        break;
    case UserPage_E:
        ui->stackedWidget->setCurrentWidget(ui->userMsg_Page);
        break;
    case SettingPage_E:
        ui->stackedWidget->setCurrentWidget(ui->setting_Page);
        break;
    case BicycleParamSet_E:
        ui->FESCar_Page->setTrainType(0);
        ui->stackedWidget->setCurrentWidget(ui->FESCar_Page);
        break;
    case FesBicycleParamSet_E:
        ui->FESCar_Page->setTrainType(1);
        ui->title_Widget->setTrainType(1);
        ui->stackedWidget->setCurrentWidget(ui->FESCar_Page);
        break;
    case FesParamSet_E:
        ui->title_Widget->setTrainType(0);
        ui->stackedWidget->setCurrentWidget(ui->FES_Page);
        break;
    case BicycleToFes_E:
        ui->stackedWidget->setCurrentWidget(ui->FES_Page);
        break;
    default:
        break;
    }
}

void CMainWindow::slotSwitchPage(E_PAGENAME page)
{
    switchPage(page);
    ui->title_Widget->setTitleByPage(page);
}

void CMainWindow::on_login_Btn_clicked()
{
    loginDialog->show();
}

void CMainWindow::slotCurrentUserChanged()
{
    ui->title_Widget->setUser(CurrentUserData::getInstace()->getCurrentPatientMsg());
}

void CMainWindow::on_startGame_Btn_clicked()
{
    process = new QProcess();
    connect(process,&QProcess::errorOccurred,[=](QProcess::ProcessError error){qDebug()<<error;});
        connect(process,QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished),[this]
                (int exitCode,QProcess::ExitStatus exitStatus){
            m_exitCode = exitCode;
            m_exitStatus = exitStatus;
            qDebug()<<"m_exitCode"<<m_exitCode<<"m_exitStatus"<<m_exitStatus;
        });
        QString path = "./GameDemo/game801/game801/MultiplayerBicycleRace.exe";

        process->start(path);
        Sleep(10);
        WId hwnd = 0;

        do{
            QEventLoop loop;
            //1ms之后退出
            QTimer::singleShot(1,&loop,SLOT(quit()));
            hwnd = (WId)FindWindow(L"UnityWndClass",L"DuoRenQiChe2");
        }while(hwnd == 0);
        m_window = QWindow::fromWinId(hwnd);
        QWidget *container = createWindowContainer(m_window,this);

        QHBoxLayout *hLayout = new QHBoxLayout(this);
        hLayout->setMargin(0);
        hLayout->addWidget(container);
        ui->game_widget->setLayout(hLayout);
}

void CMainWindow::slot_Timerout()
{
    m_gameDisplayPage->show();
}
