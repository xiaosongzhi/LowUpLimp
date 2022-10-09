#include "gamedisplaypage.h"
#include "ui_gamedisplaypage.h"
#include "mainwindowpagecontrol.h"
#include <QPropertyAnimation>
#include <QButtonGroup>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
GameDisplayPage::GameDisplayPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameDisplayPage),
    m_openState(true),
    upDirection(0),
    downDirection(0),
    m_spasmTipsDialog(NULL)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);    //设置透明
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

    ui->stop_Btn->setVisible(false);
    ui->pause_Btn->setVisible(false);

    m_spasmTipsDialog = new SpasmTipsDialog();

    setTitle();

}

GameDisplayPage::~GameDisplayPage()
{
    if(m_leftAnimation)
        delete m_leftAnimation;
    if(m_rightAnimation)
        delete m_rightAnimation;
    delete ui;
}

void GameDisplayPage::setUser(const ST_PatientMsg &st_patientMsg)
{
    ui->user_Btn->setText(st_patientMsg.name);
}

void GameDisplayPage::setTitle()
{
    ui->title_Label->setText(tr("游戏训练"));

    //设置title效果
    ui->user_Btn->setIcon(QIcon(":/DependFile/Source/User/user1.png"));
    ui->user_Btn->setIconSize(QSize(40,40));
}

void GameDisplayPage::setTrainPart(int type)
{
    switch(type)
    {
    case 0:
        ui->upLimp_GroupBox->setVisible(true);
        ui->downLimp_GroupBox->setVisible(false);
        break;
    case 1:
        ui->upLimp_GroupBox->setVisible(false);
        ui->downLimp_GroupBox->setVisible(true);
        break;
    case 2:
        ui->upLimp_GroupBox->setVisible(true);
        ui->downLimp_GroupBox->setVisible(true);
        break;
    }
}

void GameDisplayPage::on_start_Btn_clicked()
{
    m_spasmTipsDialog->show();
    ui->start_Btn->setVisible(false);
    ui->stop_Btn->setVisible(true);
    ui->pause_Btn->setVisible(true);
}

void GameDisplayPage::open_Btn_clicked()
{
    m_leftAnimation->setStartValue(QPoint(-430,120));
    m_leftAnimation->setEndValue(QPoint(0,120));
    m_rightAnimation->setStartValue(QPoint(1920,120));
    m_rightAnimation->setEndValue(QPoint(1490,120));
    m_leftAnimation->start(QAbstractAnimation::KeepWhenStopped);
    m_rightAnimation->start(QAbstractAnimation::KeepWhenStopped);
}

void GameDisplayPage::close_Btn_clicked()
{
    m_leftAnimation->setStartValue(QPoint(0,120));
    m_leftAnimation->setEndValue(QPoint(-430,120));
    m_rightAnimation->setStartValue(QPoint(1490,120));
    m_rightAnimation->setEndValue(QPoint(1920,120));
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
            m_channelAList.at(i)->setText(QString::number(data[i]));

}

void GameDisplayPage::setChannelBData(int *data,int size)
{
    if(size <= 8 )
        for(int i = 0;i <size;i++)
            m_channelBList.at(i)->setText(QString::number(data[i]));

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
    ui->start_Btn->setVisible(true);
    ui->stop_Btn->setVisible(false);
    ui->pause_Btn->setVisible(false);

    MainWindowPageControl::getInstance()->setCurrentPage(MainPage_E);
}

void GameDisplayPage::on_pause_Btn_clicked()
{
    m_spasmTipsDialog->close();
    ui->start_Btn->setVisible(true);
    ui->stop_Btn->setVisible(false);
    ui->pause_Btn->setVisible(false);
}


void GameDisplayPage::on_switchAFes_Btn_clicked()
{
    if(ui->switchAFes_Btn->styleSheet() == "border-image: url(:/DependFile/Source/gamePage/switchOn.png);")
    {
        ui->switchAFes_Btn->setStyleSheet("border-image: url(:/DependFile/Source/gamePage/switchOff.png);");
    }
    else if(ui->switchAFes_Btn->styleSheet() == "border-image: url(:/DependFile/Source/gamePage/switchOff.png);")
    {
        ui->switchAFes_Btn->setStyleSheet("border-image: url(:/DependFile/Source/gamePage/switchOn.png);");
    }
}


void GameDisplayPage::on_switchBFes_Btn_clicked()
{
    if(ui->switchBFes_Btn->styleSheet() == "border-image: url(:/DependFile/Source/gamePage/switchOn.png);")
    {
        ui->switchBFes_Btn->setStyleSheet("border-image: url(:/DependFile/Source/gamePage/switchOff.png);");
    }
    else if(ui->switchBFes_Btn->styleSheet() == "border-image: url(:/DependFile/Source/gamePage/switchOff.png);")
    {
        ui->switchBFes_Btn->setStyleSheet("border-image: url(:/DependFile/Source/gamePage/switchOn.png);");
    }
}

//填充实时下位机反馈参数
void GameDisplayPage::setRealTimeParam(int updown,int remainTime,int speed,int power)
{
    //上肢
    if(0 == updown)
    {
        ui->upRemainTime_Label->setText(QString::number(remainTime));
        ui->upRealSpeed_Label->setText(QString::number(speed));
        ui->upRealPower_Label->setText(QString::number(power));
    } //下肢
    else if(1 == updown)
    {
        ui->downRemainTime_Label->setText(QString::number(remainTime));
        ui->downRealSpeed_Label->setText(QString::number(speed));
        ui->downRealPower_Label->setText(QString::number(power));
    }

}
//填充设置参数
void GameDisplayPage::fillSetParam(int updown,int speed,int resistance,int direction)
{
    //上肢
    if(0 == updown)
    {
        upDirection = direction;
        if(upDirection == 0)
            on_upForward_Btn_clicked();
        else if(upDirection == 1)
            on_upBackward_Btn_clicked();
        ui->upSpeed_Label->setText(QString::number(speed));
        ui->upForce_Label->setText(QString::number(resistance));
    }//下肢
    else if(1 == updown)
    {
        downDirection = direction;
        if(downDirection == 0)
            on_downBackward_Btn_clicked();
        else if(downDirection == 1)
            on_downForward_Btn_clicked();
        ui->downSpeed_Label->setText(QString::number(speed));
        ui->downForce_Label->setText(QString::number(resistance));
    }
}

void GameDisplayPage:: setPulseOxygen(const ST_PulseOxygen& pulseOxygen)
{
    ui->pulse_Label->setText(QString::number(pulseOxygen.pulse));
    ui->oxygen_Label->setText(QString::number(pulseOxygen.oxygen));
}

void GameDisplayPage::setCenterParam(int left, int right, int length)
{
    ui->leftBalance_Label->setText(QString::number(left) + "%");
    ui->leftBalance_Label->setText(QString::number(right) + "%");
    ui->leftBalance_Label->setText(QString::number(length) + "m");
}

void GameDisplayPage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,10));
}
