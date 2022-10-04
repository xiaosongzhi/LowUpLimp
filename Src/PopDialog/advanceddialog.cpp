#include "advanceddialog.h"
#include "ui_advanceddialog.h"
#include <QPaintEvent>
#include <QPainter>
AdvancedDialog::AdvancedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdvancedDialog),
    fesSwitchFlag(true),
    isSkipPassive(true)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);    //设置透明
    setAttribute(Qt::WA_DeleteOnClose);
    st_advanceParam.isFesOn = fesSwitchFlag;
    st_advanceParam.isSkipPassive = isSkipPassive;
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
    st_advanceParam.speedLimit = ui->speedLimit_Btn->currentText().toInt();
    //消极阶段
    st_advanceParam.negativeSpeedCompensate = ui->negativeSpeedCompensate_ComboBox->currentText().toInt();
    st_advanceParam.tiredContinueTime = ui->tiredContinueTime_comboBox->currentText().toInt();
    st_advanceParam.tiredSpeedCompensate = ui->tiredSpeedCompensate_comboBox->currentText().toInt();

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
