#include "advanceddialog.h"
#include "ui_advanceddialog.h"
#include <QPaintEvent>
#include <QPainter>
#include <QListView>
AdvancedDialog::AdvancedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedDialog),
    fesSwitchFlag(true),
    isSkipPassive(true)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);    //设置透明

    st_advanceParam.isFesOn = fesSwitchFlag;
    st_advanceParam.isSkipPassive = isSkipPassive;

    initWidgetData();
}

AdvancedDialog::~AdvancedDialog()
{
    delete ui;
}

void AdvancedDialog::on_confirm_Btn_clicked()
{
    st_advanceParam.isFesOn = fesSwitchFlag;
    st_advanceParam.isSkipPassive = isSkipPassive;
    //预热阶段
    st_advanceParam.preheatContinueTime = ui->preheatContinueTime_ComboBox->currentText().toInt();
    st_advanceParam.preheatAContinueTime = ui->preheatAContinueTime_ComboBox->currentText().toInt();
    st_advanceParam.preheatCompensate = ui->preheatCompensate_ComboBox->currentText().toInt();
    st_advanceParam.preheatMaxPower = ui->preheatMaxPower_ComboBox->currentText().toInt();
    st_advanceParam.transitionalFesRise = ui->transitionalFesRise_ComboBox->currentText().toInt();
    //积极治疗阶段
    st_advanceParam.positiveFChiXuTime = ui->positiveFChiXuTime_ComboBox->currentText().toInt();
    st_advanceParam.positiveFControlSpeed = ui->positiveFControlSpeed_ComboBox->currentText().toInt();
    st_advanceParam.positiveBChiXuTime = ui->positiveBChiXuTime_ComboBox->currentText().toInt();
    st_advanceParam.positiveBSpeedCompensate = ui->positiveBSpeedCompensate_ComboBox->currentText().toInt();
    st_advanceParam.positiveBresistance = ui->positiveBresistance_ComboBox->currentText().toInt();
    st_advanceParam.timeLimit = ui->timeLimit_ComboBox->currentText().toInt();
    st_advanceParam.speedLimit = ui->speedLimit_ComboBox->currentText().toInt();
    //消极阶段
    st_advanceParam.negativeSpeedCompensate = ui->negativeSpeedCompensate_ComboBox->currentText().toInt();
    st_advanceParam.tiredContinueTime = ui->tiredContinueTime_ComboBox->currentText().toInt();
    st_advanceParam.tiredSpeedCompensate = ui->tiredSpeedCompensate_ComboBox->currentText().toInt();

    this->close();
}

void AdvancedDialog::on_cancel_Btn_clicked()
{
    this->close();
}


void AdvancedDialog::on_skipPassive_Btn_clicked()
{
    if(ui->skipPassive_Btn->styleSheet() == "border-image: url(:/DependFile/Source/gamePage/switchOn.png);")
    {
        isSkipPassive = false;
        ui->skipPassive_Btn->setStyleSheet("border-image: url(:/DependFile/Source/gamePage/switchOff.png);");
    }
    else if(ui->skipPassive_Btn->styleSheet() == "border-image: url(:/DependFile/Source/gamePage/switchOff.png);")
    {
        isSkipPassive = true;
        ui->skipPassive_Btn->setStyleSheet("border-image: url(:/DependFile/Source/gamePage/switchOn.png);");
    }
}


void AdvancedDialog::on_preheatFesSwitch_Btn_clicked()
{
    if(ui->preheatFesSwitch_Btn->styleSheet() == "border-image: url(:/DependFile/Source/gamePage/switchOn.png);")
    {
        fesSwitchFlag = false;
        ui->preheatFesSwitch_Btn->setStyleSheet("border-image: url(:/DependFile/Source/gamePage/switchOff.png);");
    }
    else if(ui->preheatFesSwitch_Btn->styleSheet() == "border-image: url(:/DependFile/Source/gamePage/switchOff.png);")
    {
        fesSwitchFlag = true;
        ui->preheatFesSwitch_Btn->setStyleSheet("border-image: url(:/DependFile/Source/gamePage/switchOn.png);");
    }
}

void AdvancedDialog::initWidgetData()
{
    //预热阶段
    //加速时间/加速持续时间
    for(int i = 0;i <= 60;i++)
    {
        ui->preheatContinueTime_ComboBox->addItem(QString::number(i));
        ui->preheatAContinueTime_ComboBox->addItem(QString::number(i));
    }
    //转速补偿
    for(int i = -30;i <= 30;i++ )
        ui->preheatCompensate_ComboBox->addItem(QString::number(i));
    //最大电量
    for(int i =0;i <=50 ;i++)
        ui->preheatMaxPower_ComboBox->addItem(QString::number(i));
    //电刺激上升幅度
    for(int i = 0;i <= 100; i++)
        ui->transitionalFesRise_ComboBox->addItem(QString::number(i));

    //积极阶段
    for(int i = 0; i <= 120; i++)
        ui->positiveFChiXuTime_ComboBox->addItem(QString::number(i));
    for(int i = 5;i <= 60;i++)
        ui->positiveFControlSpeed_ComboBox->addItem(QString::number(i));
    for(int i = 0; i <= 120; i++)
        ui->positiveBChiXuTime_ComboBox->addItem(QString::number(i));
    for(int i = -30;i <= 30; i++)
        ui->positiveBSpeedCompensate_ComboBox->addItem(QString::number(i));
    for(int i = -20;i <= 20;i++)
        ui->positiveBresistance_ComboBox->addItem(QString::number(i));
    for(int i = 0;i <= 240;i++)
        ui->timeLimit_ComboBox->addItem(QString::number(i));
    for(int i = 1;i <= 50;i++ )
        ui->speedLimit_ComboBox->addItem(QString::number(i*(-1)));

    //消极阶段
    for(int i = -30;i <= 30;i++)
        ui->negativeSpeedCompensate_ComboBox->addItem(QString::number(i));
    for(int i = 0;i <= 30;i ++)
        ui->tiredContinueTime_ComboBox->addItem(QString::number(i));
    for(int i = 0;i <= 30;i++)
        ui->tiredSpeedCompensate_ComboBox->addItem(QString::number(i*(-1)));

    foreach (QObject* obj, ui->groupBox->children()) {
        if(obj->objectName().contains("ComboBox"))
        {
            QComboBox *combox = static_cast<QComboBox*>(obj);
            combox->setView(new QListView);
        }
    }

    foreach (QObject* obj, ui->groupBox_2->children()) {
        if(obj->objectName().contains("ComboBox"))
        {
            QComboBox *combox = static_cast<QComboBox*>(obj);
            combox->setView(new QListView);
        }
    }

    foreach (QObject* obj, ui->groupBox_3->children()) {
        if(obj->objectName().contains("ComboBox"))
        {
            QComboBox *combox = static_cast<QComboBox*>(obj);
            combox->setView(new QListView);
        }
    }
}

ST_AdvancedParam AdvancedDialog::getValue()
{
    return st_advanceParam;
}

void AdvancedDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
