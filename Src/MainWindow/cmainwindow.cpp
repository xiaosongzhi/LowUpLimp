#include "cmainwindow.h"
#include "ui_cmainwindow.h"
#include "mainwindowpagecontrol.h"
CMainWindow::CMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<E_PAGENAME>("E_PAGENAME");
    connect(MainWindowPageControl::getInstance(),SIGNAL(signalSwitchPage(E_PAGENAME)),this,SLOT(slotSwitchPage(E_PAGENAME)));

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
    case CarParamSet_E:
        ui->stackedWidget->setCurrentWidget(ui->FESCar_Page);
        break;
    case FesParamSet_E:
        ui->stackedWidget->setCurrentWidget(ui->FES_Page);
        break;
    }
}

void CMainWindow::slotSwitchPage(E_PAGENAME page)
{
    switchPage(page);
}
int pageIndex = 0;
void CMainWindow::on_test_Btn_clicked()
{
    MainWindowPageControl::getInstance()->setCurrentPage(pageIndex);
    ++pageIndex;
    if(pageIndex == 5)
        pageIndex = 0;
}

