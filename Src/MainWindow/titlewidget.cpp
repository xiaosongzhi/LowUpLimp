#include "titlewidget.h"
#include "ui_titlewidget.h"
#include <QPixmap>
#include <windows.h>
#include <wlanapi.h>
#include "mainwindowpagecontrol.h"
#include <QDebug>
TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget),
    checkTimer(nullptr)
{
    ui->setupUi(this);
    connect(ui->back1_Btn,SIGNAL(clicked()),this,SLOT(slotBackClicked()));
    connect(ui->back2_Btn,SIGNAL(clicked()),this,SLOT(slotBackClicked()));

    ui->user_Btn->setIcon(QIcon(":/DependFile/Source/User/user1.png"));
    ui->user_Btn->setIconSize(QSize(40,40));

    setBackBtnVisible(false);

    checkTimer = new QTimer();
    checkTimer->setInterval(3000);
    connect(checkTimer,SIGNAL(timeout()),this,SLOT(slotCheckTimer()));
    checkTimer->start();

}

TitleWidget::~TitleWidget()
{
    delete ui;
}


void TitleWidget::slotBackClicked()
{

    int currentPage = MainWindowPageControl::getInstance()->getCurrentPageIndex();

    switch(currentPage)
    {
    case MainPage_E:
    case UserPage_E:
    case SettingPage_E:
    case BicycleParamSet_E:
    case FesBicycleParamSet_E:
        MainWindowPageControl::getInstance()->setCurrentPage(MainPage_E);
        break;
    case FesParamSet_E:
    {
        //分两种情况
        switch(m_trainType)
        {
        case 0://1、直接选择的FES训练跳到主界面
            MainWindowPageControl::getInstance()->setCurrentPage(MainPage_E);
            break;
        case 1://2、从踏车界面跳转到FES界面,跳到踏车界面
            MainWindowPageControl::getInstance()->setCurrentPage(FesBicycleParamSet_E);
            break;
        }
    }
        break;
    case BicycleToFes_E:
        MainWindowPageControl::getInstance()->setCurrentPage(FesBicycleParamSet_E);
        break;
    }
}
//设置当前用户
void TitleWidget::setUser(const ST_PatientMsg& st_patientMsg)
{
    ui->user_Btn->setText(st_patientMsg.name);
}
//设置wifi信号强度
void TitleWidget::setSignalStrength(int value)
{
    Q_UNUSED(value)
}
//设置标题
void TitleWidget::setTitleByPage(E_PAGENAME pageType)
{
    QString title;
    switch(pageType)
    {
    case MainPage_E:
        title = tr("功能选择");
        setBackBtnVisible(false);
        break;
    case TrainingPage_E:
        title = tr("游戏训练");//上肢、下肢、四肢训练
        setBackBtnVisible(false);
        break;
    case UserPage_E:
        title = tr("用户管理");
        setBackBtnVisible(true);
        break;
    case SettingPage_E:
        title = tr("软件设置");
        setBackBtnVisible(true);
        break;
    case BicycleParamSet_E:
        title = tr("踏车参数");
        setBackBtnVisible(true);
        break;
    case FesParamSet_E:
        setBackBtnVisible(true);
        title = tr("FES参数");
        break;
    case FesBicycleParamSet_E:
        setBackBtnVisible(true);
        title = tr("踏车参数");
        break;
    default:
        break;
    }
    ui->title_Label->setText(title);
}

void TitleWidget::setTrainType(int8_t type)
{
    m_trainType = type;
}

void TitleWidget::on_user_Btn_clicked()
{
    MainWindowPageControl::getInstance()->setCurrentPage(UserPage_E);
}

void TitleWidget::slotCheckTimer()
{
    showWIFI();
}

void TitleWidget::showWIFI()
{
    DWORD dwError = ERROR_SUCCESS;
    DWORD dwNegotiatedVersion;
    HANDLE hClientHandle = NULL;
    dwError = WlanOpenHandle(1, NULL, &dwNegotiatedVersion, &hClientHandle);
    if (dwError != ERROR_SUCCESS)
    {
        WlanCloseHandle(hClientHandle,NULL);
        return;
    }
    PWLAN_INTERFACE_INFO_LIST pInterfaceList = NULL;
    dwError = WlanEnumInterfaces(hClientHandle, NULL,&pInterfaceList);
    if ( dwError != ERROR_SUCCESS )
    {
        WlanFreeMemory(pInterfaceList);
        WlanCloseHandle(hClientHandle,NULL);
        return;
    }

    GUID &guid = pInterfaceList->InterfaceInfo[0].InterfaceGuid;
    PWLAN_AVAILABLE_NETWORK_LIST pWLAN_AVAILABLE_NETWORK_LIST = NULL;

    dwError = WlanGetAvailableNetworkList(hClientHandle, &guid,
        2,NULL, &pWLAN_AVAILABLE_NETWORK_LIST);
    if (dwError != ERROR_SUCCESS)
    {
        WlanFreeMemory(pInterfaceList);
        WlanFreeMemory(pWLAN_AVAILABLE_NETWORK_LIST);
        WlanCloseHandle(hClientHandle,NULL);
        return;
    }
    WLAN_AVAILABLE_NETWORK wlanAN;
    bool isConnected=false;
    int numberOfItems = pWLAN_AVAILABLE_NETWORK_LIST->dwNumberOfItems;
    if (numberOfItems > 0)
    {
        for(int i = 0; i <numberOfItems; i++)
        {
            wlanAN = pWLAN_AVAILABLE_NETWORK_LIST->Network[i];
            if(wlanAN.dwFlags & 1)
            {
                isConnected=true;

                int wifiQuality=(int)wlanAN.wlanSignalQuality;

                if(wifiQuality>75)
                {
                    QPixmap pixmapWireless(":/DependFile/Source/signal/wifi3.png");
                    ui->wifiSignal_Label->setPixmap(pixmapWireless);
                }
                else if(wifiQuality>50&&wifiQuality<=75)
                {
                    QPixmap pixmapWireless(":/DependFile/Source/signal/wifi2.png");
                    ui->wifiSignal_Label->setPixmap(pixmapWireless);
                }
                else if(wifiQuality>25&&wifiQuality<=50)
                {
                    QPixmap pixmapWireless(":/DependFile/Source/signal/wifi1.png");
                    ui->wifiSignal_Label->setPixmap(pixmapWireless);
                }
                else if(wifiQuality>0&&wifiQuality<=25)
                {
                    QPixmap pixmapWireless(":/icons/WirelessIcon3.png");
                    ui->wifiSignal_Label->setPixmap(pixmapWireless);
                }

            }
        }
    }
    if (!isConnected)
    {
        QPixmap pixmapWireless(":/icons/WirelessIcon4.png");
        ui->wifiSignal_Label->setPixmap(pixmapWireless);
    }
    WlanFreeMemory(pInterfaceList);
    WlanFreeMemory(pWLAN_AVAILABLE_NETWORK_LIST);
    WlanCloseHandle(hClientHandle,NULL);
}

void  TitleWidget::setBackBtnVisible(bool visible)
{
    ui->back1_Btn->setVisible(visible);
    ui->back2_Btn->setVisible(visible);
}
