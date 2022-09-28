#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include "mainwindowpagecontrol.h"
#include "currentuserdata.h"
#include <QDebug>
CMainWindow::CMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    qRegisterMetaType<E_PAGENAME>("E_PAGENAME");
    connect(MainWindowPageControl::getInstance(),SIGNAL(signalSwitchPage(E_PAGENAME)),this,SLOT(slotSwitchPage(E_PAGENAME)));
    connect(CurrentUserData::getInstace(),SIGNAL(signalUserChanged()),this,SLOT(slotCurrentUserChanged()));
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







