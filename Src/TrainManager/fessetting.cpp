#include "fessetting.h"
#include "ui_fessetting.h"
#include "festotalparamdialog.h"
#include "channeldialog.h"
#include "mainwindowpagecontrol.h"
#include "icemodule.h"
#include <QDebug>
FesSetting::FesSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FesSetting),
    m_FesTotalParamDialog(nullptr),
    m_ChannelDialog(nullptr)
{
    ui->setupUi(this);
    initWidget();

    for(int i  = 0;i < 30;i++)
        FESABoxList<<true;

    //默认显示A电刺激盒
    ui->stackedWidget->setCurrentIndex(0);
}

FesSetting::~FesSetting()
{
    if(m_FesTotalParamDialog)
        delete m_FesTotalParamDialog;
    if(m_ChannelDialog)
        delete m_ChannelDialog;
    delete ui;
}

void FesSetting::initWidget()
{
    ui->trainTime_Widget->initButton(tr("训练时间"),"min");
    ui->frequent_Widget->initButton(tr("全局频率"),"Hz");
    ui->upTime_Widget->initButton(tr("上升时间"),"s");
    ui->downTime_Widget->initButton(tr("下降时间"),"s");
    ui->openTime_Widget->initButton(tr("打开时间"),"s");
    ui->closeTime_Widget->initButton(tr("关闭时间"),"s");


    ui->channelA1_Widget->initWidget(tr("通道1"),1);
    channelList.append(ui->channelA1_Widget);
    ui->channelA2_Widget->initWidget(tr("通道2"),2);
    channelList.append(ui->channelA2_Widget);
    ui->channelA3_Widget->initWidget(tr("通道3"),3);
    channelList.append(ui->channelA3_Widget);
    ui->channelA4_Widget->initWidget(tr("通道4"),4);
    channelList.append(ui->channelA4_Widget);
    ui->channelA5_Widget->initWidget(tr("通道5"),5);
    channelList.append(ui->channelA5_Widget);
    ui->channelA6_Widget->initWidget(tr("通道6"),6);
    channelList.append(ui->channelA6_Widget);
    ui->channelA7_Widget->initWidget(tr("通道7"),7);
    channelList.append(ui->channelA7_Widget);
    ui->channelA8_Widget->initWidget(tr("通道8"),8);
    channelList.append(ui->channelA8_Widget);

    ui->channelB1_Widget->initWidget(tr("通道1"),9);
    channelList.append(ui->channelB1_Widget);
    ui->channelB2_Widget->initWidget(tr("通道2"),10);
    channelList.append(ui->channelB2_Widget);
    ui->channelB3_Widget->initWidget(tr("通道3"),11);
    channelList.append(ui->channelB3_Widget);
    ui->channelB4_Widget->initWidget(tr("通道4"),12);
    channelList.append(ui->channelB4_Widget);
    ui->channelB5_Widget->initWidget(tr("通道5"),13);
    channelList.append(ui->channelB5_Widget);
    ui->channelB6_Widget->initWidget(tr("通道6"),14);
    channelList.append(ui->channelB6_Widget);
    ui->channelB7_Widget->initWidget(tr("通道7"),15);
    channelList.append(ui->channelB7_Widget);
    ui->channelB8_Widget->initWidget(tr("通道8"),16);
    channelList.append(ui->channelB8_Widget);


    foreach(QWidget *widget,channelList)
        connect(widget,SIGNAL(buttonClicked(int)),this,SLOT(slotChannelWidgetClicked(int)));

    connect(ui->trainTime_Widget,SIGNAL(buttonClicked()),this,SLOT(slotTrainTimeBtnClicked()));
    connect(ui->frequent_Widget,SIGNAL(buttonClicked()),this,SLOT(slotFrequentBtnClicked()));
    connect(ui->upTime_Widget,SIGNAL(buttonClicked()),this,SLOT(slotUpTimeBtnClicked()));
    connect(ui->downTime_Widget,SIGNAL(buttonClicked()),this,SLOT(slotDownTimeBtnClicked()));
    connect(ui->openTime_Widget,SIGNAL(buttonClicked()),this,SLOT(slotOpenTimeBtnClicked()));
    connect(ui->closeTime_Widget,SIGNAL(buttonClicked()),this,SLOT(slotCloseTimeBtnClicked()));


    QButtonGroup *buttonGroup = new QButtonGroup();
    buttonGroup->addButton(ui->FESA_Btn);
    buttonGroup->addButton(ui->FESB_Btn);
    //    buttonGroup->setExclusive(true);

    m_FesTotalParamDialog = new FesTotalParamDialog();
    m_ChannelDialog = new ChannelDialog();
}


void FesSetting::setChannelState()
{

}

void FesSetting::slotChannelWidgetClicked(int id)
{
    int channel = id;
    if(channel > 8)
        channel-=8;
    m_ChannelDialog->setTitle(QString(tr("通道%1").arg(channel)));
    m_ChannelDialog->setMuscleState(FESABoxList);
    //显示通道对话框
    m_ChannelDialog->show();
    m_ChannelDialog->exec();
    ST_MuscleParam st_MuscleParam = m_ChannelDialog->getValue();

    FESABoxList[st_MuscleParam.muscleId-1] = false;
    MuscleButton* muscleChannel = dynamic_cast<MuscleButton*>(channelList.at(id-1));
    muscleChannel->setMuscleParamButton(st_MuscleParam);

    //根据状态设置按钮的状态
    muscleChannel->setMuscleEnabled(st_MuscleParam.connectState);

}

void FesSetting::slotTrainTimeBtnClicked()
{
    m_FesTotalParamDialog->setTitleAndUnit(tr("训练时间"),"min");
    int oldValue = ui->trainTime_Widget->getValue();
    m_FesTotalParamDialog->setValue(oldValue);
    m_FesTotalParamDialog->show();
    m_FesTotalParamDialog->exec();
    int newValue = m_FesTotalParamDialog->getValue();
    ui->trainTime_Widget->setData(newValue);
}

void FesSetting::slotFrequentBtnClicked()
{
    m_FesTotalParamDialog->setTitleAndUnit(tr("全局频率"),"Hz");
    int oldValue = ui->frequent_Widget->getValue();
    m_FesTotalParamDialog->setValue(oldValue);
    m_FesTotalParamDialog->show();
    m_FesTotalParamDialog->exec();
    int newValue = m_FesTotalParamDialog->getValue();
    ui->frequent_Widget->setData(newValue);
}

void FesSetting::slotUpTimeBtnClicked()
{
    m_FesTotalParamDialog->setTitleAndUnit(tr("上升时间"),"s");
    int oldValue = ui->upTime_Widget->getValue();
    m_FesTotalParamDialog->setValue(oldValue);
    m_FesTotalParamDialog->show();
    m_FesTotalParamDialog->exec();
    int newValue = m_FesTotalParamDialog->getValue();
    ui->upTime_Widget->setData(newValue);
}

void FesSetting::slotDownTimeBtnClicked()
{
    m_FesTotalParamDialog->setTitleAndUnit(tr("下降时间"),"s");
    int oldValue = ui->downTime_Widget->getValue();
    m_FesTotalParamDialog->setValue(oldValue);
    m_FesTotalParamDialog->show();
    m_FesTotalParamDialog->exec();
    int newValue = m_FesTotalParamDialog->getValue();
    ui->downTime_Widget->setData(newValue);
}

void FesSetting::slotOpenTimeBtnClicked()
{
    m_FesTotalParamDialog->setTitleAndUnit(tr("打开时间"),"s");
    int oldValue = ui->openTime_Widget->getValue();
    m_FesTotalParamDialog->setValue(oldValue);
    m_FesTotalParamDialog->show();
    m_FesTotalParamDialog->exec();
    int newValue = m_FesTotalParamDialog->getValue();
    ui->openTime_Widget->setData(newValue);
}

void FesSetting::slotCloseTimeBtnClicked()
{
    m_FesTotalParamDialog->setTitleAndUnit(tr("关闭时间"),"s");
    int oldValue = ui->closeTime_Widget->getValue();
    m_FesTotalParamDialog->setValue(oldValue);
    m_FesTotalParamDialog->show();
    m_FesTotalParamDialog->exec();
    int newValue = m_FesTotalParamDialog->getValue();
    ui->closeTime_Widget->setData(newValue);
}

void FesSetting::on_FESA_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void FesSetting::on_FESB_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//从该界面启动游戏
void FesSetting::on_OK_Btn_clicked()
{
    MainWindowPageControl::getInstance()->setCurrentPage(TrainingPage_E);
    int array[8] = {0};
    //获取界面上FesA的设置值
    for(int i = 0;i < 8;i++)
    {
        MuscleButton* muscleChannel = dynamic_cast<MuscleButton*>(channelList.at(i));
        ST_MuscleParam st_muscleParam = muscleChannel->getMuscleParam();
        array[i] = st_muscleParam.maxCurrent;
    }
    IceModule::getInstance()->setFesAParam(array,8);
    //获取界面上FesB的设置值
    for(int i = 8;i < 16;i++)
    {
        MuscleButton* muscleChannel = dynamic_cast<MuscleButton*>(channelList.at(i));
        ST_MuscleParam st_muscleParam = muscleChannel->getMuscleParam();
        qDebug()<<st_muscleParam.muscleId;
        array[i-8] = st_muscleParam.maxCurrent;
    }
    IceModule::getInstance()->setFesAParam(array,8);

}

