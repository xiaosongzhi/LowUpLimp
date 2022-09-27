#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include "mainwindowpagecontrol.h"
#include <QDebug>
CMainWindow::CMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<E_PAGENAME>("E_PAGENAME");
    connect(MainWindowPageControl::getInstance(),SIGNAL(signalSwitchPage(E_PAGENAME)),this,SLOT(slotSwitchPage(E_PAGENAME)));

    advancedDialog = new AdvancedDialog();
    channelDialog = new ChannelDialog();
    deleteUserDialog = new DeleteUserDialog();
    emergencyDialog = new EmergencyStopDialog();
    fesTipsDialog = new FesTipsDialog();
    fesTotalParamDialog = new FesTotalParamDialog();
    selectUserDialog = new SelectUserDialog();
    spasmTipsDialog = new SpasmTipsDialog();
    userDialog = new UserDialog();
    gameDiplayPage = new GameDisplayPage();
    loginDialog = new LoginWidget();
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
    case TrainingPage_E:
        break;
    case UserPage_E:
        ui->stackedWidget->setCurrentWidget(ui->userMsg_Page);
        break;
    case SettingPage_E:
        ui->stackedWidget->setCurrentWidget(ui->setting_Page);
        break;
    case BicycleParamSet_E:
        ui->stackedWidget->setCurrentWidget(ui->FESCar_Page);
        break;
    case FesParamSet_E:
        ui->stackedWidget->setCurrentWidget(ui->FES_Page);
        break;
    default:
        break;

    }
}

void CMainWindow::slotSwitchPage(E_PAGENAME page)
{
    switchPage(page);
}

void CMainWindow::on_advanced_Btn_clicked()
{
    advancedDialog->show();
}


void CMainWindow::on_trainPage_Btn_clicked()
{
    deleteUserDialog->show();
    gameDiplayPage->show();
}


void CMainWindow::on_jipian_Btn_clicked()
{
    fesTipsDialog->show();
}


void CMainWindow::on_spasm_Btn_clicked()
{
    spasmTipsDialog->show();
}


void CMainWindow::on_emergency_Btn_clicked()
{
    emergencyDialog->show();
}


void CMainWindow::on_channel_Btn_clicked()
{
    channelDialog->show();
}


void CMainWindow::on_allParam_Btn_clicked()
{
    fesTotalParamDialog->show();
}


void CMainWindow::on_login_Btn_clicked()
{
    loginDialog->show();
}


void CMainWindow::on_select_clicked()
{
    qDebug()<<"select";
    selectUserDialog->show();
}


void CMainWindow::on_delete_2_clicked()
{
    qDebug()<<"delete";
    deleteUserDialog->show();
}


void CMainWindow::on_new_2_clicked()
{
    qDebug()<<"new";
    userDialog->setDialogTitle(E_NEW_USER);
}

