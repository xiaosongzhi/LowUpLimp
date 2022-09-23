#include "gamedisplaypage.h"
#include "ui_gamedisplaypage.h"
#include <QPropertyAnimation>
#include <QButtonGroup>
#include <QDebug>
GameDisplayPage::GameDisplayPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameDisplayPage),
    m_openState(true)
{
    ui->setupUi(this);
    m_leftAnimation = new QPropertyAnimation(ui->leftPage_GroupBox,"pos");
    m_rightAnimation = new QPropertyAnimation(ui->rightPage_GroupBox,"pos");
    m_leftAnimation->setDuration(1000);
    m_rightAnimation->setDuration(1000);

    QButtonGroup *upLimpGroup = new QButtonGroup(this);
    upLimpGroup->addButton(ui->upForward_Btn);
    upLimpGroup->addButton(ui->upBackward_Btn);

    QButtonGroup *downLimpGroup = new QButtonGroup(this);
    downLimpGroup->addButton(ui->downBackward_Btn);
    downLimpGroup->addButton(ui->downForward_Btn);

    m_channelAList.append(ui->channelA1_Label);
    m_channelAList.append(ui->channelA2_Label);
    m_channelAList.append(ui->channelA3_Label);
    m_channelAList.append(ui->channelA4_Label);
    m_channelAList.append(ui->channelA5_Label);
    m_channelAList.append(ui->channelA6_Label);
    m_channelAList.append(ui->channelA7_Label);
    m_channelAList.append(ui->channelA8_Label);

    m_channelBList.append(ui->channelB1_Label);
    m_channelBList.append(ui->channelB2_Label);
    m_channelBList.append(ui->channelB3_Label);
    m_channelBList.append(ui->channelB4_Label);
    m_channelBList.append(ui->channelB5_Label);
    m_channelBList.append(ui->channelB6_Label);
    m_channelBList.append(ui->channelB7_Label);
    m_channelBList.append(ui->channelB8_Label);
}

GameDisplayPage::~GameDisplayPage()
{
    if(m_leftAnimation)
        delete m_leftAnimation;
    if(m_rightAnimation)
        delete m_rightAnimation;
    delete ui;
}

void GameDisplayPage::on_start_Btn_clicked()
{
    m_leftAnimation->start(QAbstractAnimation::KeepWhenStopped);
}

void GameDisplayPage::open_Btn_clicked()
{
    m_leftAnimation->setStartValue(QPoint(-430,0));
    m_leftAnimation->setEndValue(QPoint(0,0));
    m_rightAnimation->setStartValue(QPoint(1920,0));
    m_rightAnimation->setEndValue(QPoint(1490,0));
    m_leftAnimation->start(QAbstractAnimation::KeepWhenStopped);
    m_rightAnimation->start(QAbstractAnimation::KeepWhenStopped);
}

void GameDisplayPage::close_Btn_clicked()
{
    m_leftAnimation->setStartValue(QPoint(0,0));
    m_leftAnimation->setEndValue(QPoint(-430,0));
    m_rightAnimation->setStartValue(QPoint(1490,0));
    m_rightAnimation->setEndValue(QPoint(1920,0));
    m_leftAnimation->start(QAbstractAnimation::KeepWhenStopped);
    m_rightAnimation->start(QAbstractAnimation::KeepWhenStopped);
}

void GameDisplayPage::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    if(m_openState)
        close_Btn_clicked();
    else
        open_Btn_clicked();
    m_openState = !m_openState;
}

void GameDisplayPage::on_upSpeedMinus_Btn_clicked()
{
    int speed = ui->upSpeed_Label->text().toInt();
    if(speed > 2)
    ui->upSpeed_Label->setText(QString::number(--speed));
}

void GameDisplayPage::on_upSpeedPlus_Btn_clicked()
{
    int speed = ui->upSpeed_Label->text().toInt();
    if(speed < 60)
    ui->upSpeed_Label->setText(QString::number(++speed));
}

void GameDisplayPage::on_upForceMinus_Btn_clicked()
{
    int force = ui->upForce_Label->text().toInt();
    if(force > 0)
        ui->upForce_Label->setText(QString::number(--force));
}

void GameDisplayPage::on_upForcePlus_Btn_clicked()
{
    int force = ui->upForce_Label->text().toInt();
    if(force < 29)
        ui->upForce_Label->setText(QString::number(++force));
}

void GameDisplayPage::on_upForward_Btn_clicked()
{

}

void GameDisplayPage::on_upBackward_Btn_clicked()
{

}

void GameDisplayPage::on_downSpeedMinus_Btn_clicked()
{
    int speed = ui->downSpeed_Label->text().toInt();
    if(speed > 2)
    ui->downSpeed_Label->setText(QString::number(--speed));
}

void GameDisplayPage::on_downSpeedPlus_Btn_clicked()
{
    int speed = ui->downSpeed_Label->text().toInt();
    if(speed < 60)
    ui->downSpeed_Label->setText(QString::number(++speed));
}

void GameDisplayPage::on_downForceMinus_Btn_clicked()
{
    int force = ui->downForce_Label->text().toInt();
    if(force > 0)
        ui->downForce_Label->setText(QString::number(--force));
}

void GameDisplayPage::on_downForcePlus_Btn_clicked()
{
    int force = ui->downForce_Label->text().toInt();
    if(force < 29)
        ui->downForce_Label->setText(QString::number(++force));
}

void GameDisplayPage::on_downForward_Btn_clicked()
{

}

void GameDisplayPage::on_downBackward_Btn_clicked()
{

}

void GameDisplayPage::setChannelAData(int *data,int size)
{
    if(size <= 8 )
    for(int i = 0;i <size;i++)
    {
        m_channelAList.at(i)->setText(QString::number(data[i]));
    }
}

void GameDisplayPage::setChannelBData(int *data,int size)
{
    if(size <= 8 )
    for(int i = 0;i <size;i++)
    {
        m_channelBList.at(i)->setText(QString::number(data[i]));
    }
}

void GameDisplayPage::setTrainSpeed(int speed, qint8 type)
{
    Q_UNUSED(speed)
    Q_UNUSED(type)
}

void GameDisplayPage::setTrainFore(int force, qint8 type)
{
    Q_UNUSED(force)
    Q_UNUSED(type)
}

void GameDisplayPage::setTrainDirection(qint8 direction, qint8 type)
{
    Q_UNUSED(direction)
    Q_UNUSED(type)
}

void GameDisplayPage::switchFes(qint8 channel, bool ok)
{
    Q_UNUSED(channel)
    Q_UNUSED(ok)
}

void GameDisplayPage::on_stop_Btn_clicked()
{

}


void GameDisplayPage::on_pause_Btn_clicked()
{

}

