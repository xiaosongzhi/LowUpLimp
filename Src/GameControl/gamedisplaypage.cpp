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
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include "currentuserdata.h"
#include "paramtipsdialog.h"
#include "gamecontrol.h"
GameDisplayPage::GameDisplayPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameDisplayPage),
    m_openState(true),
    upDirection(1),
    downDirection(1),
    m_spasmTipsDialog(NULL),
    heartTimer(NULL),
    countDownTimer(NULL),
    m_spasmTimes(0),
    m_currentMode(0),
    m_reportDialog(NULL),
    m_quitDialog(NULL),
    m_emergencyDialog(NULL),
    heartCount(0)
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

    m_emergencyDialog = new EmergencyStopDialog();

    setTitle();

    connect(IceModule::getInstance(),SIGNAL(signalSetFesAParam(int*,int)),this,SLOT(slotSetChannelAData(int*,int)));
    connect(IceModule::getInstance(),SIGNAL(signalSetFesBParam(int*,int)),this,SLOT(slotSetChannelBData(int*,int)));
    connect(IceModule::getInstance(),SIGNAL(signalSetBicycleParam(ST_BicycleParam)),this,SLOT(slotSetBicycleParam(ST_BicycleParam)));

    connect(CCommunicateAPI::getInstance(),SIGNAL(signalReadyRead(QByteArray)),this,SLOT(slotReceiveData(QByteArray)));

    heartTimer = new QTimer();
    connect(heartTimer,SIGNAL(timeout()),this,SLOT(slotHeartTimer()));
    heartTimer->setInterval(1000);
#ifdef HEARTBEAT
    heartTimer->start();
#endif
    countDownTimer = new QTimer();
    countDownTimer->setInterval(1000);
    connect(countDownTimer,SIGNAL(timeout()),this,SLOT(slotCountDownTimer()));
    initGameSocket();

    m_reportDialog = new TrainReport();

    m_quitDialog = new QuitGameDialog();

    connect(ui->back1_Btn,SIGNAL(clicked()),this,SLOT(slotBackClicked()));
    connect(ui->back2_Btn,SIGNAL(clicked()),this,SLOT(slotBackClicked()));

    ui->warnTips_Label->setVisible(false);

    st_trainReport.passiveTime = 0;
    st_trainReport.activeTime = 0;

    ui->start_Btn_2->setVisible(false);
    ui->stop_Btn_2->setVisible(false);
}

GameDisplayPage::~GameDisplayPage()
{
    if(m_leftAnimation)
        delete m_leftAnimation;
    if(m_rightAnimation)
        delete m_rightAnimation;
    if(heartTimer)
        delete heartTimer;
    if(countDownTimer)
        delete countDownTimer;
    if(m_reportDialog)
        delete m_reportDialog;
    if(m_quitDialog)
        delete m_quitDialog;
    if(m_emergencyDialog)
        delete m_emergencyDialog;
    delete ui;
}

void GameDisplayPage::initGameSocket()
{
    m_gameSocket = new QUdpSocket();
    int16_t port = 20000;

    if(m_gameSocket->bind(QHostAddress("127.0.0.1"),port))
    {
        qDebug()<<(QString("游戏服务端口%1").arg(port));
    }
    connect(m_gameSocket,&QUdpSocket::readyRead,this,&GameDisplayPage::slotReceiveGameData);
}

void GameDisplayPage::setUser(const ST_PatientMsg &st_patientMsg)
{
    ui->user_Btn->setText(st_patientMsg.name);
}

void GameDisplayPage::setTitle()
{

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
        ui->upLimp_GroupBox->move(10,10);
        ui->upLimp_GroupBox->setVisible(true);
        ui->downLimp_GroupBox->setVisible(false);
        ui->title_Label->setText(tr("上肢训练"));
        break;
    case 1:
        ui->downLimp_GroupBox->move(10,10);
        ui->upLimp_GroupBox->setVisible(false);
        ui->downLimp_GroupBox->setVisible(true);
        ui->title_Label->setText(tr("下肢训练"));
        break;
    case 2:
        ui->upLimp_GroupBox->move(10,10);
        ui->downLimp_GroupBox->move(10,583);
        ui->upLimp_GroupBox->setVisible(true);
        ui->downLimp_GroupBox->setVisible(true);
        ui->title_Label->setText(tr("四肢训练"));
        break;
    }
}

//实时数据填充
void GameDisplayPage::setSlaveParam(ST_DeviceParam &st_deviceParam)
{
    ST_GameControlParam st_gameControlParam;
    switch(m_bodyPart)
    {
    case 0: //上肢
    {
        ui->upRealSpeed_Label->setText(QString::number(st_deviceParam.upLimpSpeed));
        ui->upRealPower_Label->setText(QString::number(st_deviceParam.upPower));
        setTrainMode(st_deviceParam.currentMode);
        //运动距离怎么计算
        ui->length_Label->setText(QString::number(st_deviceParam.upLimpCircle*0.628,'f',2) + "m");
        st_gameControlParam.speed = st_deviceParam.upLimpSpeed;

        st_gameControlParam.forceLeft = st_deviceParam.upBalance;
        st_gameControlParam.forceRight = 100 - st_deviceParam.upBalance;
    }
        break;
    case 1: //下肢
    {
        ui->downRealSpeed_Label->setText(QString::number(st_deviceParam.downLimpSpeed));
        ui->downRealPower_Label->setText(QString::number(st_deviceParam.downPower));
        setTrainMode(st_deviceParam.currentMode);
        ui->length_Label->setText(QString::number(st_deviceParam.downLimpCircle*0.628,'f',2) + "m");
        st_gameControlParam.speed = st_deviceParam.downLimpSpeed;

        st_gameControlParam.forceLeft = st_deviceParam.downBalance;
        st_gameControlParam.forceRight = 100 - st_deviceParam.downBalance;

    }
        break;
    case 2: //上下肢
    {
        ui->upRealSpeed_Label->setText(QString::number(st_deviceParam.upLimpSpeed));
        ui->upRealPower_Label->setText(QString::number(st_deviceParam.upPower));
        ui->downRealSpeed_Label->setText(QString::number(st_deviceParam.downLimpSpeed));
        ui->downRealPower_Label->setText(QString::number(st_deviceParam.downPower));
        setTrainMode(st_deviceParam.currentMode);
        ui->length_Label->setText(QString::number(st_deviceParam.upLimpCircle*0.628,'f',2) + "m");

        if(st_deviceParam.upLimpSpeed >= st_deviceParam.downLimpSpeed)
        {
            st_gameControlParam.forceLeft = st_deviceParam.upBalance;
            st_gameControlParam.forceRight = 100 - st_deviceParam.upBalance;
        }
        else
        {
            st_gameControlParam.forceLeft = st_deviceParam.downBalance;
            st_gameControlParam.forceRight = 100 - st_deviceParam.downBalance;
        }

        st_gameControlParam.speed = st_deviceParam.upLimpSpeed > st_deviceParam.downLimpSpeed?st_deviceParam.upLimpSpeed:st_deviceParam.downLimpSpeed;
    }
        break;
    }

    st_trainReport.upLimpLength = st_deviceParam.upLimpCircle*0.628;
    st_trainReport.downLimpLength = st_deviceParam.downLimpCircle*0.628;

    //此处显示的是左右平衡，但是下位机上传的是上下肢平衡
    ui->leftBalance_Label->setText(QString::number(st_gameControlParam.forceLeft));
    ui->rightBalance_Label->setText(QString::number(st_gameControlParam.forceRight));

    //驱动游戏
    sendGameControlParam(st_gameControlParam);

    static int skipNum = 0;
    ++skipNum;
    if(skipNum > 20)
    {
        QPair<int,int> balancePair;
        balancePair.first = st_deviceParam.upBalance;
        balancePair.second = st_deviceParam.downBalance;

        //左右平衡计数
        balanceList.append(balancePair);
    }

    if(1 == st_deviceParam.spasmState )
    {
        if(m_spasmTipsDialog->isVisible())
            return;
        m_spasmTimes++;
        //痉挛次数用于报告
        st_trainReport.spasmTimes = m_spasmTimes;
        m_spasmTipsDialog->setSpasmDialogVisible(true,m_spasmTimes);
        if(m_spasmTimes >= 3)
        {
            m_spasmTimes = 0;
            //大于3次痉挛退出训练
            on_stop_Btn_clicked();
        }
    }

    //过速保护
    if( 1 == st_deviceParam.overSpeedProtect)
    {

    }

    //触发急停
    if( 1 == st_deviceParam.emergencyState)
    {
        if(m_emergencyDialog->isVisible())
            return;
        m_emergencyDialog->show();
        //退出训练
        countDownTimer->stop();
        sendStopCmd();
        this->close();
        emit signalGameStateChanged(0);
        //返回参数设置界面
        MainWindowPageControl::getInstance()->setCurrentPage(BicycleParamSet_E);

    }
    else
    {
        if(m_emergencyDialog->isVisible())
            m_emergencyDialog->close();
    }
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

    if(event->pos().x() > 434 && event->pos().x() < 1482)
    {
        if(m_openState)
            close_Btn_clicked();
        else
            open_Btn_clicked();
        m_openState = !m_openState;
    }

}

void GameDisplayPage::on_upSpeedMinus_Btn_clicked()
{
    int speed = ui->upSpeed_Label->text().toInt();
    if(speed > 2)
    {
        --speed;
        ui->upSpeed_Label->setText(QString::number(speed));
#ifdef UNIFORMLY
        ui->downSpeed_Label->setText(QString::number(speed));
#endif
        setTrainSpeed(speed);
        m_st_bicycleParam.speed = speed;
    }
}

void GameDisplayPage::on_upSpeedPlus_Btn_clicked()
{
    int speed = ui->upSpeed_Label->text().toInt();

    if(speed < 60)
    {
        ++speed;
        ui->upSpeed_Label->setText(QString::number(speed));
#ifdef UNIFORMLY
        ui->downSpeed_Label->setText(QString::number(speed));
#endif
        setTrainSpeed(speed);
        m_st_bicycleParam.speed = speed;
    }

}

void GameDisplayPage::on_upForceMinus_Btn_clicked()
{
    int force = ui->upForce_Label->text().toInt();
    if(force > 0)
    {
        --force;
        ui->upForce_Label->setText(QString::number(force));
#ifdef UNIFORMLY
        ui->downForce_Label->setText(QString::number(force));
#endif
        setTrainFore(force);
        m_st_bicycleParam.resistance = force;
    }
}

void GameDisplayPage::on_upForcePlus_Btn_clicked()
{
    int force = ui->upForce_Label->text().toInt();
    if(force < 20)
    {
        ++force;
        ui->upForce_Label->setText(QString::number(force));
#ifdef UNIFORMLY
        ui->downForce_Label->setText(QString::number(force));
#endif
        setTrainFore(force);
        m_st_bicycleParam.resistance = force;
    }
}

void GameDisplayPage::on_upForward_Btn_clicked()
{
    setTrainDirection(1);
    m_st_bicycleParam.direction = 1;
#ifdef UNIFORMLY
    ui->downForward_Btn->setChecked(true);
#endif
}

void GameDisplayPage::on_upBackward_Btn_clicked()
{
    setTrainDirection(0);
    m_st_bicycleParam.direction = 0;
#ifdef UNIFORMLY
    ui->downBackward_Btn->setChecked(true);
#endif
}

void GameDisplayPage::on_downSpeedMinus_Btn_clicked()
{
    int speed = ui->downSpeed_Label->text().toInt();
    if(speed > 2)
    {
        --speed;
        ui->downSpeed_Label->setText(QString::number(speed));
#ifdef UNIFORMLY
        ui->upSpeed_Label->setText(QString::number(speed));
#endif
        setTrainSpeed(speed);
        m_st_bicycleParam.speed = speed;
    }

}

void GameDisplayPage::on_downSpeedPlus_Btn_clicked()
{
    int speed = ui->downSpeed_Label->text().toInt();
    if(speed < 60)
    {
        ++speed;
        ui->downSpeed_Label->setText(QString::number(speed));
#ifdef UNIFORMLY
        ui->upSpeed_Label->setText(QString::number(speed));
#endif
        setTrainSpeed(speed);
        m_st_bicycleParam.speed = speed;
    }

}

void GameDisplayPage::on_downForceMinus_Btn_clicked()
{
    int force = ui->downForce_Label->text().toInt();
    if(force > 0)
    {
        --force;
        ui->downForce_Label->setText(QString::number(force));
#ifdef UNIFORMLY
        ui->upForce_Label->setText(QString::number(force));
#endif
        setTrainFore(force);
        m_st_bicycleParam.resistance = force;
    }

}

void GameDisplayPage::on_downForcePlus_Btn_clicked()
{
    int force = ui->downForce_Label->text().toInt();
    if(force < 20)
    {
        ++force;
        ui->downForce_Label->setText(QString::number(force));
#ifdef UNIFORMLY
        ui->upForce_Label->setText(QString::number(force));
#endif
        setTrainFore(force);
        m_st_bicycleParam.resistance = force;
    }

}

void GameDisplayPage::on_downForward_Btn_clicked()
{
    setTrainDirection(1);
    m_st_bicycleParam.direction = 1;
#ifdef UNIFORMLY
    ui->upForward_Btn->setChecked(true);
#endif
}

void GameDisplayPage::on_downBackward_Btn_clicked()
{
    setTrainDirection(0);
    m_st_bicycleParam.direction = 0;
#ifdef UNIFORMLY
    ui->upBackward_Btn->setChecked(true);
#endif
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

/*******踏车设置参数*******/
void GameDisplayPage::slotSetBicycleParam(ST_BicycleParam st_setBicycleParam)
{
    m_st_bicycleParam = st_setBicycleParam;
    m_startNum = m_st_bicycleParam.trainTime * 60;

    m_spasmTipsDialog->setSpasmCompletedDirection(st_setBicycleParam.spasmType);
    //训练模式
    setTrainMode(m_st_bicycleParam.trainMode);
    //主被动模式按钮状态切换
    switchButtonState(m_st_bicycleParam.trainMode);
    //设置训练部位
    setTrainPart(st_setBicycleParam.bodyPart);
    //上肢
    if(0 == st_setBicycleParam.bodyPart || 2 == st_setBicycleParam.bodyPart)
    {
        //主动训练速度设置成2
        if(1 == m_st_bicycleParam.trainMode)
            st_setBicycleParam.speed = 2;
        ui->upSpeed_Label->setText(QString::number(st_setBicycleParam.speed));

        ui->upForce_Label->setText(QString::number(st_setBicycleParam.resistance));
        ui->upRemainTime_Label->setText(QString::number(m_st_bicycleParam.trainTime));
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
    if(1 == st_setBicycleParam.bodyPart || 2 == st_setBicycleParam.bodyPart)
    {
        //主动训练速度设置成2
        if(1 == m_st_bicycleParam.trainMode)
            st_setBicycleParam.speed = 2;
        ui->downSpeed_Label->setText(QString::number(st_setBicycleParam.speed));
        ui->downForce_Label->setText(QString::number(st_setBicycleParam.resistance));
        ui->downRemainTime_Label->setText(QString::number(m_st_bicycleParam.trainTime));
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

    st_patientMsg = CurrentUserData::getInstace()->getCurrentPatientMsg();

    //填充报告内容
    //患者基础信息
    st_trainReport.ID = st_patientMsg.ID;
    st_trainReport.name = st_patientMsg.name;
    st_trainReport.sex = st_patientMsg.sex;
    st_trainReport.phone = st_patientMsg.phone;
    st_trainReport.age = st_patientMsg.age;
    st_trainReport.markMsg = st_patientMsg.markMsg;
    //训练设置参数
    st_trainReport.trainMode = m_st_bicycleParam.trainMode;
    st_trainReport.bodyIndex = m_st_bicycleParam.bodyPart;
    st_trainReport.trainTime = m_st_bicycleParam.trainTime;

    //初始化平衡值
    st_trainReport.leftBalance = 0;
    st_trainReport.rightBalance = 0;

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
        ++heartCount;
        break;
    }
}

void GameDisplayPage::slotHeartTimer()
{
    CCommunicateAPI::getInstance()->sendHeartBeat();
    static int num = 0;
    ++num;
    if(num > 3)
    {
        num = 0;
        if(heartCount < 1)
        {
            //通信已断开
            qDebug()<<"通信已断开";
        }
        if(heartCount >= 3)
        {
            heartCount = 0;
        }
    }
}

void GameDisplayPage::slotCountDownTimer()
{
    --m_startNum;

    if(m_startNum < 0)
    {
        countDownTimer->stop();
        return;
    }

    int minNum = m_startNum/60;//分钟数
    int secNum = m_startNum%60;//秒数

    //计算主被动时间

    switch(m_currentMode)
    {
    case 0: //被动
        ++st_trainReport.passiveTime;
        break;
    case 1://主动
        ++st_trainReport.activeTime;
    case 9:
        st_trainReport.passiveTime+=2;
        break;
    case 10:
        st_trainReport.activeTime += 2;
        break;
    case 11:
    case 12:
        ++st_trainReport.passiveTime;
        ++st_trainReport.activeTime;
        break;
    }

    //填入阻力值
    resistentList<<ui->upForce_Label->text().toInt();

    if(minNum == 0 && secNum == 0)
    {
        m_startNum = 0;
        //关闭定时器
        countDownTimer->stop();

        ui->upRemainTime_Label->setText("0");
        ui->downRemainTime_Label->setText("0");
        //告知下位机停止训练
        m_st_bicycleParam.controlState = 0;
        CCommunicateAPI::getInstance()->sendBicycleParam(m_st_bicycleParam);
        //弹出报告
        //计算结果数据（平衡度、距离等）
        calculateResultData();
        //弹出训练报告
        m_reportDialog->setReportData(st_trainReport,1);

        //开窗
        if(!m_openState)
        {
            open_Btn_clicked();
            m_openState = !m_openState;
        }

        st_trainReport.passiveTime = 0;
        st_trainReport.activeTime = 0;

        sendStopCmd();

        emit signalGameStateChanged(0);
    }
    else
    {
        ui->upRemainTime_Label->setText(QString::number(minNum+1));
        ui->downRemainTime_Label->setText(QString::number(minNum+1));
    }
}

void GameDisplayPage::slotReceiveGameData()
{
    while(m_gameSocket->hasPendingDatagrams())
    {
        QByteArray buf;
        buf.resize(m_gameSocket->pendingDatagramSize());
        m_gameSocket->readDatagram(buf.data(),buf.size());
        parseGameMsg(buf);
    }
}

void GameDisplayPage::slotBackClicked()
{
    m_quitDialog->exec();
    if(m_quitDialog->getResult() == 1)
    {
        //开窗
        if(!m_openState)
        {
            open_Btn_clicked();
            m_openState = !m_openState;
        }
        quitTrain();
        emit signalGameStateChanged(0);
    }
}

void GameDisplayPage::quitTrain()
{
    //退出训练
    m_st_bicycleParam.controlState = 0;
    CCommunicateAPI::getInstance()->sendBicycleParam(m_st_bicycleParam);
    countDownTimer->stop();
    sendStopCmd();
    this->close();
    //返回参数设置界面
    MainWindowPageControl::getInstance()->setCurrentPage(MainPage_E);
}

void GameDisplayPage::changeModeTips(QString str)
{
    ui->warnTips_Label->setVisible(true);
    ui->warnTips_Label->setText(str);
    //显示3s后隐藏
    QTimer::singleShot(3000,this,[this](){
        ui->warnTips_Label->setVisible(false);
    });
}

void GameDisplayPage::switchButtonState(int8_t mode)
{
    switch(mode)
    {
    case 0://被动不设置阻力
        //上肢速度
        ui->upSpeedMinus_Btn->setEnabled(true);
        ui->upSpeedPlus_Btn->setEnabled(true);
        ui->groupBox_2->setEnabled(true);
        //上肢阻力
        ui->upForceMinus_Btn->setEnabled(false);
        ui->upForcePlus_Btn->setEnabled(false);
        ui->groupBox_3->setEnabled(false);
        //下肢速度17
        ui->downSpeedMinus_Btn->setEnabled(true);
        ui->downSpeedPlus_Btn->setEnabled(true);
        ui->groupBox_17->setEnabled(true);
        //下肢阻力16
        ui->downForceMinus_Btn->setEnabled(false);
        ui->downForcePlus_Btn->setEnabled(false);
        ui->groupBox_16->setEnabled(false);
        break;
    case 1://主动
        //上肢速度
        ui->upSpeedMinus_Btn->setEnabled(false);
        ui->upSpeedPlus_Btn->setEnabled(false);
        ui->groupBox_2->setEnabled(false);
        //上肢阻力
        ui->upForceMinus_Btn->setEnabled(true);
        ui->upForcePlus_Btn->setEnabled(true);
        ui->groupBox_3->setEnabled(true);
        //下肢速度17
        ui->downSpeedMinus_Btn->setEnabled(false);
        ui->downSpeedPlus_Btn->setEnabled(false);
        ui->groupBox_17->setEnabled(false);
        //下肢阻力16
        ui->downForceMinus_Btn->setEnabled(true);
        ui->downForcePlus_Btn->setEnabled(true);
        ui->groupBox_16->setEnabled(true);
        break;
    default:
        //上肢速度
        ui->upSpeedMinus_Btn->setEnabled(true);
        ui->upSpeedPlus_Btn->setEnabled(true);
        ui->groupBox_2->setEnabled(true);
        //上肢阻力
        ui->upForceMinus_Btn->setEnabled(true);
        ui->upForcePlus_Btn->setEnabled(true);
        ui->groupBox_3->setEnabled(true);
        //下肢速度17
        ui->downSpeedMinus_Btn->setEnabled(true);
        ui->downSpeedPlus_Btn->setEnabled(true);
        ui->groupBox_17->setEnabled(true);
        //下肢阻力16
        ui->downForceMinus_Btn->setEnabled(true);
        ui->downForcePlus_Btn->setEnabled(true);
        ui->groupBox_16->setEnabled(true);
        break;
    }
}

//解析游戏数据
void GameDisplayPage::parseGameMsg(QByteArray jsonArray)
{
    emit signalGameStateChanged(1);

    /*
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(jsonArray, &jsonError);  // 转化为 JSON 文档
    qDebug()<<doucment.isNull();
    qDebug()<<jsonError.error;
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        qDebug()<<"@@@@@@@@@@@@@";
        if(doucment.isObject())
        {
            QJsonObject object = doucment.object();  // 转化为对象
            if(object.contains("MsgID"))
            {
                qDebug()<<"1111111111111";
                int msgID = object.value("MsgID").toInt();
                qDebug()<<msgID;
                switch(msgID)
                {
                case 3:

                    break;
                }
            }
        }
    }
    */
}

void GameDisplayPage::sendGameControlParam(ST_GameControlParam st_gameControlParam)
{
    st_gameControlParam.MsgId = 1;
    QJsonObject object;
    object.insert("MsgID",st_gameControlParam.MsgId);
    object.insert("userName",st_gameControlParam.userName);
    object.insert("ID",st_gameControlParam.ID);
    object.insert("speed",st_gameControlParam.speed);
    object.insert("forceLeft",st_gameControlParam.forceLeft);
    object.insert("forceRight",st_gameControlParam.forceRight);
    object.insert("steps",30);
    object.insert("calories",5);
    QJsonDocument document;
    document.setObject(object);
    QByteArray sendArray = document.toJson(QJsonDocument::Compact);

    QString ip("127.0.0.1");
    int16_t port = 12000;
    m_gameSocket->writeDatagram(sendArray,QHostAddress(ip),port);
}

void GameDisplayPage::sendStopCmd()
{
    QJsonObject object;
    object.insert("MsgID",2);
    object.insert("GameState",0);
    QJsonDocument document;
    document.setObject(object);
    QByteArray sendArray = document.toJson(QJsonDocument::Compact);
    QString ip("127.0.0.1");
    int16_t port = 12000;
    for(int i = 0;i < 3;i++)
    {
        m_gameSocket->writeDatagram(sendArray,QHostAddress(ip),port);
        Sleep(100);
    }
}

void GameDisplayPage::calculateResultData()
{
    //计算平衡度
    int upBalance = 0,downBalance = 0;
    int upSum = 0,downSum = 0;
    for(int i = 0;i < balanceList.size();i++)
    {
        upSum += balanceList.at(i).first;
        downSum += balanceList.at(i).second;
    }
    upBalance = ((float)upSum)/balanceList.size();
    downBalance = ((float)downSum)/balanceList.size();

    //报告中的平衡度
    switch(m_bodyPart)
    {
    case 0: //上肢
        st_trainReport.leftBalance = upBalance;
        st_trainReport.rightBalance = 100 - upBalance;
        break;
    case 1: //下肢
        st_trainReport.leftBalance = downBalance;
        st_trainReport.rightBalance = 100 - downBalance;
        break;
    case 2: //上下肢
        st_trainReport.leftBalance = upBalance;
        st_trainReport.rightBalance = 100 - upBalance;
        break;
    }

    //计算阻力值
    int maxResistent = 0,minResistent = 200,sumResistent = 0,aveResistent = 0;
    if(!resistentList.empty())
    {
        for(int i = 0;i < resistentList.size();i++)
        {
            if(maxResistent < resistentList.at(i))
                maxResistent = resistentList.at(i);
            if(minResistent > resistentList.at(i))
                minResistent = resistentList.at(i);
            sumResistent += resistentList.at(i);
        }
        if(resistentList.size() > 0)
            aveResistent = sumResistent/resistentList.size();
    }

    //参数界面设置的模式
    switch(m_st_bicycleParam.trainMode)
    {
    case 0: //被动模式
        st_trainReport.minResistance = 0;
        st_trainReport.maxResistance = 0;
        st_trainReport.averangeResistance = 0;
        break;
    default://主动
        st_trainReport.minResistance = minResistent;
        st_trainReport.maxResistance = maxResistent;
        st_trainReport.averangeResistance = aveResistent;
        break;
    }

}

void GameDisplayPage::initButton()
{
    ui->stop_Btn->setVisible(false);
    ui->pause_Btn->setVisible(false);
    ui->start_Btn->setVisible(true);
    ui->length_Label->setText("0.00m");
    ui->leftBalance_Label->setText("50%");
    ui->rightBalance_Label->setText("50%");
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

void GameDisplayPage::on_start_Btn_clicked()
{

//    if(0 == gameState)
//    {
//        if(m_st_bicycleParam.speed > 30)
//        {
//            ParamTipsDialog tipDialog;
//            tipDialog.setParamTipsMsg(tr("设定速度已超30r/min，确认使用该速度训练吗？"));
//            tipDialog.exec();
//            if(0 == tipDialog.getResult())
//                return;
//        }
//    }
    GameControl::getInstance()->playTipMusic("./DependFile/Music/startTraining.mp3");
    //已开始
    gameState = 1;

    ui->start_Btn->setVisible(false);
    ui->stop_Btn->setVisible(true);
    ui->pause_Btn->setVisible(true);

    //告知下位机开始运动
    if(m_st_bicycleParam.controlState == 2)
        m_st_bicycleParam.controlState = 3;
    else
        m_st_bicycleParam.controlState = 1;

    CCommunicateAPI::getInstance()->sendBicycleParam(m_st_bicycleParam);
    //开始时间计时器
    countDownTimer->start();

    //训练起始时间
    st_trainReport.startTimeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

}

void GameDisplayPage::on_stop_Btn_clicked()
{
    ui->start_Btn->setVisible(true);
    ui->stop_Btn->setVisible(false);
    ui->pause_Btn->setVisible(false);
    GameControl::getInstance()->playTipMusic("./DependFile/Music/stopTraining.mp3");
    //告知下位机停止训练
    m_st_bicycleParam.controlState = 0;
    CCommunicateAPI::getInstance()->sendBicycleParam(m_st_bicycleParam);
    //关闭定时器
    countDownTimer->stop();

    //计算结果数据（平衡度、距离等）
    calculateResultData();
    //弹出训练报告
    m_reportDialog->setReportData(st_trainReport,1);
    //开窗
    if(!m_openState)
    {
        open_Btn_clicked();
        m_openState = !m_openState;
    }

    //    MainWindowPageControl::getInstance()->setCurrentPage(MainPage_E);
    st_trainReport.activeTime = 0;
    st_trainReport.passiveTime = 0;
    //退出游戏
    sendStopCmd();

    emit signalGameStateChanged(0);
}

void GameDisplayPage::on_pause_Btn_clicked()
{
    GameControl::getInstance()->playTipMusic("./DependFile/Music/pauseTraining.mp3");
    //关闭定时器
    countDownTimer->stop();
    m_st_bicycleParam.controlState = 2;
    CCommunicateAPI::getInstance()->sendBicycleParam(m_st_bicycleParam);
    ui->start_Btn->setVisible(true);
    ui->stop_Btn->setVisible(false);
    ui->pause_Btn->setVisible(false);

    ui->upRealPower_Label->setText("0");
    ui->upRealSpeed_Label->setText("0");

    ui->downRealPower_Label->setText("0");
    ui->downRealSpeed_Label->setText("0");

    if(m_st_bicycleParam.trainMode == 7 || m_st_bicycleParam.trainMode == 10)
    {
        ui->upCurrentStage_Label->setText(tr("主动模式"));
        ui->downCurrentStage_Label->setText(tr("主动模式"));
        //将当前模式切成主动
        m_currentMode = 1;
    }
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
    if(m_currentMode == mode)
        return;
    if(m_currentMode != mode)
    {
        QString modeName;
        switch(mode)
        {
        case 0:
            modeName = tr("被动训练");
            ui->upCurrentStage_Label->setText(modeName);
            ui->downCurrentStage_Label->setText(modeName);
            break;
        case 1:
            modeName = tr("主动训练");
            ui->upCurrentStage_Label->setText(modeName);
            ui->downCurrentStage_Label->setText(modeName);
            break;
        case 2:
            modeName = tr("助力训练");
            ui->upCurrentStage_Label->setText(modeName);
            ui->downCurrentStage_Label->setText(modeName);
            break;
        case 3:
            modeName = tr("等速训练");
            ui->upCurrentStage_Label->setText(modeName);
            ui->downCurrentStage_Label->setText(modeName);
            break;
        case 4:
            modeName = tr("协同被动训练");
            ui->upCurrentStage_Label->setText(modeName);
            ui->downCurrentStage_Label->setText(modeName);
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
        case 9:
            ui->upCurrentStage_Label->setText(tr("被动训练"));
            ui->downCurrentStage_Label->setText(tr("被动训练"));
            break;
        case 10:
            ui->upCurrentStage_Label->setText(tr("主动训练"));
            ui->downCurrentStage_Label->setText(tr("主动训练"));
            break;
        case 11:
            ui->upCurrentStage_Label->setText(tr("主动训练"));
            ui->downCurrentStage_Label->setText(tr("被动训练"));
            break;
        case 12:
            ui->upCurrentStage_Label->setText(tr("被动训练"));
            ui->downCurrentStage_Label->setText(tr("主动训练"));
            break;
        }
        if(m_st_bicycleParam.trainMode == 7 || m_st_bicycleParam.trainMode == 10)
        {
            changeModeTips(modeName);
        }
        m_currentMode = mode;
    }

}

//填充设置参数
void GameDisplayPage::fillSetParam(int updown,int speed,int resistance,int direction)
{
    //上肢
    if(0 == updown)
    {
        upDirection = direction;
        if(upDirection == 1)
            on_upForward_Btn_clicked();
        else if(upDirection == 0)
            on_upBackward_Btn_clicked();
        ui->upSpeed_Label->setText(QString::number(speed));
        ui->upForce_Label->setText(QString::number(resistance));
    }//下肢
    else if(1 == updown)
    {
        downDirection = direction;
        if(downDirection == 1)
            on_downBackward_Btn_clicked();
        else if(downDirection == 0)
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

void GameDisplayPage::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    initButton();
    gameState = 0;//未开始
    m_spasmTimes = 0;

    ui->upRealPower_Label->setText("0");
    ui->upRealSpeed_Label->setText("0");

    ui->downRealPower_Label->setText("0");
    ui->downRealSpeed_Label->setText("0");

    balanceList.clear();
    resistentList.clear();

}


void GameDisplayPage::on_start_Btn_2_clicked()
{
//    on_start_Btn_clicked();
    ST_DeviceParam st_deviceParam;
    st_deviceParam.emergencyState = 1;
    setSlaveParam(st_deviceParam);
}

void GameDisplayPage::on_stop_Btn_2_clicked()
{
//    on_stop_Btn_clicked();
    ST_DeviceParam st_deviceParam;
    st_deviceParam.emergencyState = 0;
    setSlaveParam(st_deviceParam);
}

