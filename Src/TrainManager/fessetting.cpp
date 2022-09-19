#include "fessetting.h"
#include "ui_fessetting.h"
#include <QDebug>
FesSetting::FesSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FesSetting)
{
    ui->setupUi(this);
    initWidget();
}

FesSetting::~FesSetting()
{
    delete ui;
}

void FesSetting::on_groupBox_clicked()
{
    qDebug()<<"训练时间";
}

void FesSetting::initWidget()
{
    ui->trainTime_Widget->initButton(tr("训练时间"),"min");
    ui->frequent_Widget->initButton(tr("全局频率"),"Hz");
    ui->upTime_Widget->initButton(tr("上升时间"),"s");
    ui->downTime_Widget->initButton(tr("下降时间"),"s");
    ui->openTime_Widget->initButton(tr("打开时间"),"s");
    ui->closeTime_Widget->initButton(tr("关闭时间"),"s");

    ui->channel1_Widget->initWidget(tr("通道1"));
    ui->channel2_Widget->initWidget(tr("通道2"));
    ui->channel3_Widget->initWidget(tr("通道3"));
    ui->channel4_Widget->initWidget(tr("通道4"));
    ui->channel5_Widget->initWidget(tr("通道5"));
    ui->channel6_Widget->initWidget(tr("通道6"));
    ui->channel7_Widget->initWidget(tr("通道7"));
    ui->channel8_Widget->initWidget(tr("通道8"));
}
