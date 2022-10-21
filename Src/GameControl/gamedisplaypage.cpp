#include "gamedisplaypage.h"
#include "ui_gamedisplaypage.h"
#include "mainwindowpagecontrol.h"
#include <QPropertyAnimation>
#include <QButtonGroup>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include "icemodule.h"
#include "ccommunicateapi.h"
GameDisplayPage::GameDisplayPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameDisplayPage),
    m_openState(true),
    upDirection(0),
    downDirection(0),
    m_spasmTipsDialog(NULL),
    heartTimer(NULL)
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

    connect(IceModule::getInstance(),SIGNAL(signalSetFesAParam(int*,int)),this,SLOT(slotSetChannelAData(int*,int)));
    connect(IceModule::getInstance(),SIGNAL(signalSetFesBParam(int*,int)),this,SLOT(slotSetChannelBData(int*,int)));
    connect(IceModule::getInstance(),SIGNAL(signalSetBicycleParam(ST_BicycleParam)),this,SLOT(slotSetBicycleParam(ST_BicycleParam)));

    connect(CCommunicateAPI::getInstance(),SIGNAL(signalReadyRead(QByteArray)),this,SLOT(slotReceiveData(QByteArray)));

    heartTimer = new QTimer();
    connect(heartTimer,SIGNAL(timeout()),this,SLOT(slotHeartTimer()));
    heartTimer->setInterval(1000);
    heartTimer->start();
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
    m_bodyPart = type;
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

void GameDisplayPage::setSlaveParam(ST_DeviceParam &st_deviceParam)
{
    switch(m_bodyPart)
    {
    case 0: //上肢
    {
        ui->upRealSpeed_Label->setText(QString::number(st_deviceParam.upLimpSpeed));
        ui->upRealPower_Label->setText(QString::number(st_deviceParam.power));
        setTrainMode(st_deviceParam.currentMode);
        //运动距离怎么计算
        ui->length_Label->setText(QString::number(st_deviceParam.upLimpCircle));
    }
        break;
    case 1: //下肢
    {
        ui->downRealSpeed_Label->setText(QString::number(st_deviceParam.downLimpSpeed));
        ui->downRealPower_Label->setText(QString::number(st_deviceParam.power));
        setTrainMode(st_deviceParam.currentMode);
        ui->length_Label->setText(QString::number(st_deviceParam.downLimpCircle));
    }
        break;
    case 2: //上下肢
    {
        ui->upRealSpeed_Label->setText(QString::number(st_deviceParam.upLimpSpeed));
        ui->upRealPower_Label->setText(QString::number(st_deviceParam.power));
        ui->downRealSpeed_Label->setText(QString::number(st_deviceParam.downLimpSpeed));
        ui->downRealPower_Label->setText(QString::number(st_deviceParam.power));
        setTrainMode(st_deviceParam.currentMode);
        ui->length_Label->setText(QString::number(st_deviceParam.downLimpCircle+st_deviceParam.upLimpCircle));
    }
        break;
    }
    //此处显示的是左右平衡，但是下位机上传的是上下肢平衡
    ui->leftBalance_Label->setText(QString::number(st_deviceParam.upBalance));
    ui->rightBalance_Label->setText(QString::number(st_deviceParam.downBalance));
}

void GameDisplayPage::on_start_Btn_clicked()
{
    ui->start_Btn->setVisible(false);
    ui->stop_Btn->setVisible(true);
    ui->pause_Btn->setVisible(true);

    //告知下位机开始运动
    ST_BicycleParam st_bicycleParam;
    st_bicycleParam.controlState = 0;
    st_bicycleParam.bodyPart =2;
    st_bicycleParam.trainMode = 4;
    st_bicycleParam.spasmSwitch = 1;
    st_bicycleParam.spasmLevel = 2;
    st_bicycleParam.configPower = 0;
    st_bicycleParam.switchDirectonTime = 0;
    st_bicycleParam.phaseValue = 9;
    st_bicycleParam.direction = 1;
    st_bicycleParam.speed = 8;
    st_bicycleParam.resistance = 2;
    st_bicycleParam.spasmType = 1;
    CCommunicateAPI::getInstance()->sendBicycleParam(st_bicycleParam);
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
    {
        ui->upSpeed_Label->setText(QString::number(--speed));
        setTrainSpeed(speed);
    }

}

void GameDisplayPage::on_upSpeedPlus_Btn_clicked()
{
    int speed = ui->upSpeed_Label->text().toInt();
    if(speed < 60)
    {
        ui->upSpeed_Label->setText(QString::number(++speed));
        setTrainSpeed(speed);
    }

}

void GameDisplayPage::on_upForceMinus_Btn_clicked()
{
    int force = ui->upForce_Label->text().toInt();
    if(force > 0)
    {
        ui->upForce_Label->setText(QString::number(--force));
        setTrainFore(force);
    }
}

void GameDisplayPage::on_upForcePlus_Btn_clicked()
{
    int force = ui->upForce_Label->text().toInt();
    if(force < 29)
    {
        ui->upForce_Label->setText(QString::number(++force));
        setTrainFore(force);
    }
}

void GameDisplayPage::on_upForward_Btn_clicked()
{
    setTrainDirection(0);
}

void GameDisplayPage::on_upBackward_Btn_clicked()
{
    setTrainDirection(1);
}

void GameDisplayPage::on_downSpeedMinus_Btn_clicked()
{
    int speed = ui->downSpeed_Label->text().toInt();
    if(speed > 2)
    {
        ui->downSpeed_Label->setText(QString::number(--speed));
        setTrainSpeed(speed);
    }

}

void GameDisplayPage::on_downSpeedPlus_Btn_clicked()
{
    int speed = ui->downSpeed_Label->text().toInt();
    if(speed < 60)
    {
        ui->downSpeed_Label->setText(QString::number(++speed));
        setTrainSpeed(speed);
    }

}

void GameDisplayPage::on_downForceMinus_Btn_clicked()
{
    int force = ui->downForce_Label->text().toInt();
    if(force > 0)
    {
        ui->downForce_Label->setText(QString::number(--force));
        setTrainFore(force);
    }

}

void GameDisplayPage::on_downForcePlus_Btn_clicked()
{
    int force = ui->downForce_Label->text().toInt();
    if(force < 29)
    {
        ui->downForce_Label->setText(QString::number(++force));
        setTrainFore(force);
    }

}

void GameDisplayPage::on_downForward_Btn_clicked()
{
    setTrainDirection(0);
}

void GameDisplayPage::on_downBackward_Btn_clicked()
{
    setTrainDirection(1);
}

void GameDisplayPage::slotSetChannelAData(int *data,int size)
{
    if(size <= 8 )
        for(int i = 0;i <size;i++)
            m_channelAList.at(i)->setText(QString::number(data[i]));

}

void GameDisplayPage::slotSetChannelBData(int *data,int size)
{
    if(size <= 8 )
        for(int i = 0;i <size;i++)
            m_channelBList.at(i)->setText(QString::number(data[i]));

}

void GameDisplayPage::slotSetBicycleParam(ST_BicycleParam st_setBicycleParam)
{
    //上肢
    if(0 == st_setBicycleParam.bodyPart)
    {
        ui->upSpeed_Label->setText(QString::number(st_setBicycleParam.speed));
        ui->upForce_Label->setText(QString::number(st_setBicycleParam.resistance));
        //正向
        if(1 == st_setBicycleParam.direction)
        {
            ui->upForward_Btn->setChecked(true);
            ui->upBackward_Btn->setChecked(false);
        }
        //逆向
        else if(0 == st_setBicycleParam.direction)
        {
            ui->upForward_Btn->setChecked(false);
            ui->upBackward_Btn->setChecked(true);
        }

    }
    //下肢
    else if(1 == st_setBicycleParam.bodyPart)
    {
        ui->downSpeed_Label->setText(QString::number(st_setBicycleParam.speed));
        ui->downForce_Label->setText(QString::number(st_setBicycleParam.resistance));
        //正向
        if(1 == st_setBicycleParam.direction)
        {
            ui->downForward_Btn->setChecked(true);
            ui->downBackward_Btn->setChecked(false);
        }
        //逆向
        else if(0 == st_setBicycleParam.direction)
        {
            ui->downForward_Btn->setChecked(false);
            ui->downBackward_Btn->setChecked(true);
        }
    }
}

//接收下位机数据
void GameDisplayPage::slotReceiveData(QByteArray array)
{
    switch(array[2])
    {
    case BRFORE_START_CMD:  //启动前
        break;
    case AFTER_START_CMD:  //启动后
    {
        ST_DeviceParam  st_deviceParam;
        memcpy(&st_deviceParam,array.data() + 3,sizeof(ST_DeviceParam));
        setSlaveParam(st_deviceParam);
    }
        break;
    case RECE_HEARTBEAT_CMD:
        qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!";

        break;
    }
}

void GameDisplayPage::slotHeartTimer()
{
    CCommunicateAPI::getInstance()->sendHeartBeat();
}

void GameDisplayPage::setTrainSpeed(int speed, qint8 type)
{
    if(0 == type)
        CCommunicateAPI::getInstance()->sendRealTimeParam(PASSIVE_SPEED,speed);
    else if(1 == type)
        CCommunicateAPI::getInstance()->sendRealTimeParam(EQUAL_SPEED,speed);
}

void GameDisplayPage::setTrainFore(int force, qint8 type)
{
    Q_UNUSED(type)
    CCommunicateAPI::getInstance()->sendRealTimeParam(RESISTANCE_CMD,force);
}

void GameDisplayPage::setTrainDirection(qint8 direction, qint8 type)
{
    //direction 默认为1
    Q_UNUSED(type)
    CCommunicateAPI::getInstance()->sendRealTimeParam(SWITCH_DIRECTION,direction);
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


void GameDisplayPage::setTrainMode(int8_t mode)
{
    static int8_t currentMode = 0;

    if(currentMode != mode)
    {
        QString modeName;
        switch(mode)
        {
        case 0:
            modeName = tr("被动训练");
            break;
        case 1:
            modeName = tr("主动训练");
            break;
        case 2:
            modeName = tr("助力训练");
            break;
        case 3:
            modeName = tr("等速训练");
            break;
        case 4:
            modeName = tr("协同被动训练");
            break;
        case 5:
            modeName = tr("上肢带下肢训练");
            break;
        case 6:
            modeName = tr("下肢带上肢训练");
            break;
        case 7:
            modeName = tr("自由训练");
            break;
        case 8:
            modeName = tr("FES训练");
            break;
        }

        ui->upCurrentStage_Label->setText(modeName);
        ui->downCurrentStage_Label->setText(modeName);

        currentMode = mode;
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
