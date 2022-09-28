#include "titlewidget.h"
#include "ui_titlewidget.h"
#include <QPixmap>
#include "mainwindowpagecontrol.h"
#include <QDebug>
TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);
    connect(ui->back1_Btn,SIGNAL(clicked()),this,SLOT(slotBackClicked()));
    connect(ui->back2_Btn,SIGNAL(clicked()),this,SLOT(slotBackClicked()));

    ui->user_Btn->setIcon(QIcon(":/DependFile/Source/User/user1.png"));
    ui->user_Btn->setIconSize(QSize(40,40));

    setBackBtnVisible(false);

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

void  TitleWidget::setBackBtnVisible(bool visible)
{
    ui->back1_Btn->setVisible(visible);
    ui->back2_Btn->setVisible(visible);
}
