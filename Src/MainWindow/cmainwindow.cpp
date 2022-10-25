#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include "mainwindowpagecontrol.h"
#include "currentuserdata.h"
#include <QDebug>
#include <QTimer>
#include <windows.h>
#include <QHBoxLayout>
#include <QProcess>

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

    connect(m_gameDisplayPage,SIGNAL(signalGameStateChanged(int8_t)),this,SLOT(slotGameStateChanged(int8_t)));

    m_Process = new QProcess();
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
        on_startGame_Btn_clicked();
        QTimer::singleShot(1000,this,SLOT(slot_Timerout()));//同上，就是参数不同
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

    connect(m_Process,&QProcess::errorOccurred,[=](QProcess::ProcessError error){qDebug()<<error;});
    connect(m_Process,QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished),[this]
            (int exitCode,QProcess::ExitStatus exitStatus){
        m_exitCode = exitCode;
        m_exitStatus = exitStatus;
        qDebug()<<"m_exitCode"<<m_exitCode<<"m_exitStatus"<<m_exitStatus;
    });
    QString path = "./GameDemo/TJ_SXZ001_MultiplayerBicycleRace_LBY/MultiplayerBicycleRace_LBY.exe";
    startGame(path);

    Sleep(10);
    WId hwnd = 0;
    do{
        QEventLoop loop;
        //1ms之后退出
        QTimer::singleShot(1,&loop,SLOT(quit()));
        hwnd = (WId)FindWindow(L"UnityWndClass",L"DuoRenQiChe");
    }while(hwnd == 0);
    m_window = QWindow::fromWinId(hwnd);
    container = createWindowContainer(m_window,this);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->setMargin(0);
    hLayout->addWidget(container);
    if(ui->game_widget->layout() != NULL)
        delete ui->game_widget->layout();
    ui->game_widget->setLayout(hLayout);

}

void CMainWindow::slotGameStateChanged(int8_t state)
{
    switch(state)
    {
    case 0: //停止游戏
        qDebug()<<"停止游戏";
        switchPage(MainPage_E);
        m_gameDisplayPage->close();
        break;
    case 1: //开始游戏
        break;
    }
}

void CMainWindow::startGame(QString path)
{
    //1.开启游戏进程
    if(path.isEmpty())
        return;
    QString hardDisk = path.mid(0,2);
    hardDisk.append("\n\r");

    QString gameName = path.mid(path.lastIndexOf('/')+1);
    gameName.prepend("start ");
    gameName.append("\n\r");
    QString gamePath = path.mid(0,path.lastIndexOf('/'));
    gamePath.prepend("cd ");
    gamePath.append("\n\r");
    m_Process->start("cmd.exe");
    //切换盘符
    m_Process->write(hardDisk.toLatin1());
    //进入文件夹
    m_Process->write(gamePath.toLatin1());
    //开启进程
    m_Process->write(gameName.toLatin1());
    m_Process->write("exit\n\r");
    m_Process->waitForFinished();
    m_Process->close();
    //2.关闭设备复位中的界面
}

void CMainWindow::slot_Timerout()
{
    m_gameDisplayPage->show();
}
