#include "armorleg.h"
#include "ui_armorleg.h"
#include "advanceddialog.h"
#include "mainwindowpagecontrol.h"
#include <QListView>
#include "icemodule.h"
#include <QDebug>
ArmOrLeg::ArmOrLeg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmOrLeg),
    m_advanceDialog(NULL)
{
    ui->setupUi(this);
    m_advanceDialog = new AdvancedDialog();
    initWidget();
    ui->stackedWidget->setCurrentIndex(0);
    ui->advanced1_Btn->setVisible(false);
}

ArmOrLeg::~ArmOrLeg()
{
    if(m_advanceDialog)
        delete m_advanceDialog;
    delete ui;
}

void ArmOrLeg::initWidget()
{

    ui->resistance1_ComboBox->setView(new QListView);
    ui->speed1_ComboBox->setView(new QListView);
    ui->trainTime1_ComboBox->setView(new QListView);

    ui->upTrainTime2_ComboBox->setView(new QListView);
    //    ui->downTrainTime2_ComboBox->setView(new QListView);

    ui->upResistance2_ComboBox->setView(new QListView);
    //    ui->downResistance2_ComboBox->setView(new QListView);

    ui->upSpeed2_ComboBox->setView(new QListView);
    //    ui->downSpeed2_ComboBox->setView(new QListView);
    ui->advanced1_Btn->setVisible(false);

    //填充数据
    //速度
    for(int i = 2;i <= 60; i++)
    {
        ui->speed1_ComboBox->addItem(QString::number(i));
        ui->upSpeed2_ComboBox->addItem(QString::number(i));
    }
    //阻力 0~20挡
    for(int i = 0;i <= 20;i++)
    {
        ui->resistance1_ComboBox->addItem(QString::number(i));
        ui->upResistance2_ComboBox->addItem(QString::number(i));
    }
    //时间
    for(int i = 1;i <= 120;i++)
    {
        ui->trainTime1_ComboBox->addItem(QString::number(i));
        ui->upTrainTime2_ComboBox->addItem(QString::number(i));
    }


}

void ArmOrLeg::setTrainType(int8_t type)
{
    if(0 == type)
    {
        ui->confirm_Btn->setVisible(true);
        ui->next_Btn->setVisible(false);
    }
    else if(1 == type)
    {
        ui->confirm_Btn->setVisible(false);
        ui->next_Btn->setVisible(true);
    }
}

void ArmOrLeg::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    ui->spasmCW1_RadioButton->setChecked(true);
    ui->spasmCW2_RadioButton->setChecked(true);
}

void ArmOrLeg::on_upDownLimp_RadioButton_toggled(bool checked)
{
    if(checked)
        ui->stackedWidget->setCurrentIndex(1);
    else
        ui->stackedWidget->setCurrentIndex(0);
}

//单上肢、下肢高级设置
void ArmOrLeg::on_advanced1_Btn_clicked()
{
    m_advanceDialog->show();
    m_advanceDialog->exec();
    ST_AdvancedParam st_advancedParam = m_advanceDialog->getValue();
    Q_UNUSED(st_advancedParam)
}

//四肢中的上肢
void ArmOrLeg::on_upAdvanced2_Btn_clicked()
{
    m_advanceDialog->show();
    m_advanceDialog->exec();
    ST_AdvancedParam st_advancedParam = m_advanceDialog->getValue();
    Q_UNUSED(st_advancedParam)
}

//四肢中的下肢
void ArmOrLeg::on_downAdvanced2_Btn_clicked()
{
    m_advanceDialog->show();
    m_advanceDialog->exec();
    ST_AdvancedParam st_advancedParam = m_advanceDialog->getValue();
    Q_UNUSED(st_advancedParam)
}

//下一步--进入FES界面
void ArmOrLeg::on_next_Btn_clicked()
{
    MainWindowPageControl::getInstance()->setCurrentPage(BicycleToFes_E);
}

//确认参数--进入游戏
void ArmOrLeg::on_confirm_Btn_clicked()
{
    MainWindowPageControl::getInstance()->setCurrentPage(TrainingPage_E);
    ST_BicycleParam st_bicycleParam;
    //训练部位
    if(ui->upLimp_RadioButton->isChecked())
        st_bicycleParam.bodyPart = 0;
    else if(ui->downLimp_RadioButton->isChecked())
        st_bicycleParam.bodyPart = 1;
    else if(ui->upDownLimp_RadioButton->isChecked())
    {
        st_bicycleParam.bodyPart = 2;

        //训练模式
        if(ui->activePassive2_RadioButton->isChecked())
            st_bicycleParam.trainMode = 7;  //四肢主被动
        else if(ui->passive2_RadioButton->isChecked())
            st_bicycleParam.trainMode = 4;  //四肢纯被动
        //训练时间
        st_bicycleParam.trainTime = ui->upTrainTime2_ComboBox->currentText().toUInt();
        //训练阻力
        st_bicycleParam.resistance = ui->upResistance2_ComboBox->currentText().toInt();
        //训练速度
        st_bicycleParam.speed = ui->upSpeed2_ComboBox->currentText().toInt();
        //转向
        if(ui->CW2_RadioButton->isChecked())
            st_bicycleParam.direction = 1;
        else if(ui->ACW2_RadioButton->isChecked())
            st_bicycleParam.direction = 0;
        //痉挛保护
        if(ui->spasmACW2_RadioButton->isChecked())
            st_bicycleParam.spasmType = 0;
        else if(ui->spasmCW2_RadioButton->isChecked())
            st_bicycleParam.spasmType = 1;

        if(ui->spasmClose2_RadioButton->isChecked())
            st_bicycleParam.spasmSwitch = 0;
        else
            st_bicycleParam.spasmSwitch = 1;

        //痉挛等级
        if(ui->spasmLow2_RadioButton->isChecked())
            st_bicycleParam.spasmLevel = 1;
        else if(ui->spasmMidd2_RadioButton->isChecked())
            st_bicycleParam.spasmLevel = 2;
        else if(ui->spasmHigh2_RadioButton->isChecked())
            st_bicycleParam.spasmLevel = 3;
    }

    //单肢
    if(!ui->upDownLimp_RadioButton->isChecked())
    {
        //单肢训练模式
        if(ui->passive1_RadioButton->isChecked())
            st_bicycleParam.trainMode = 0;
        else if(ui->active1_RadioButton->isChecked())
            st_bicycleParam.trainMode = 1;
        else if(ui->assistant1_RadioButton->isChecked())
            st_bicycleParam.trainMode = 2;
        else if(ui->constant1_RadioButton->isChecked())
            st_bicycleParam.trainMode = 3;
        else if(ui->activePassive1_RadioButton->isChecked())
            st_bicycleParam.trainMode = 4;

        //训练时间
        st_bicycleParam.trainTime = ui->trainTime1_ComboBox->currentText().toUInt();
        //训练阻力
        st_bicycleParam.resistance = ui->resistance1_ComboBox->currentText().toInt();
        //训练速度
        st_bicycleParam.speed = ui->speed1_ComboBox->currentText().toInt();


        //转向
        if(ui->CW1_RadioButton->isChecked())
            st_bicycleParam.direction = 1;
        else if(ui->ACW1_RadioButton->isChecked())
            st_bicycleParam.direction = 0;
        //痉挛保护
        if(ui->spasmACW1_RadioButton->isChecked())
            st_bicycleParam.spasmType = 0;
        else if(ui->spasmCW1_RadioButton->isChecked())
            st_bicycleParam.spasmType = 1;

        if(ui->spasmClose1_RadioButton->isChecked())
            st_bicycleParam.spasmSwitch = 0;
        else
            st_bicycleParam.spasmSwitch = 1;

        //痉挛等级
        if(ui->spasmLow1_RadioButton->isChecked())
            st_bicycleParam.spasmLevel = 1;
        else if(ui->spasmMidd1_RadioButton->isChecked())
            st_bicycleParam.spasmLevel = 2;
        else if(ui->spasmHigh1_RadioButton->isChecked())
            st_bicycleParam.spasmLevel = 3;

    }
    st_bicycleParam.controlState = 0;
    IceModule::getInstance()->setBicycleParam(st_bicycleParam);

}


void ArmOrLeg::on_spasmClose2_RadioButton_toggled(bool checked)
{
    ui->groupBox_17->setEnabled(!checked);
}


void ArmOrLeg::on_spasmClose1_RadioButton_toggled(bool checked)
{
    ui->groupBox_8->setEnabled(!checked);
}

