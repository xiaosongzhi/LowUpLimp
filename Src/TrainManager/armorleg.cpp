#include "armorleg.h"
#include "ui_armorleg.h"
#include "advanceddialog.h"
#include "mainwindowpagecontrol.h"
#include <QListView>
#include <QDebug>
ArmOrLeg::ArmOrLeg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmOrLeg),
    m_advanceDialog(NULL)
{
    ui->setupUi(this);
    m_advanceDialog = new AdvancedDialog();
    initWidget();
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
    ui->downTrainTime2_ComboBox->setView(new QListView);

    ui->upResistance2_ComboBox->setView(new QListView);
    ui->downResistance2_ComboBox->setView(new QListView);

    ui->upSpeed2_ComboBox->setView(new QListView);
    ui->downSpeed2_ComboBox->setView(new QListView);
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
}

//四肢中的上肢
void ArmOrLeg::on_upAdvanced2_Btn_clicked()
{
    m_advanceDialog->show();
    m_advanceDialog->exec();
    ST_AdvancedParam st_advancedParam = m_advanceDialog->getValue();
}

//四肢中的下肢
void ArmOrLeg::on_downAdvanced2_Btn_clicked()
{
    m_advanceDialog->show();
    m_advanceDialog->exec();
    ST_AdvancedParam st_advancedParam = m_advanceDialog->getValue();
}

void ArmOrLeg::on_next_Btn_clicked()
{
    MainWindowPageControl::getInstance()->setCurrentPage(BicycleToFes_E);
}


void ArmOrLeg::on_confirm_Btn_clicked()
{
    MainWindowPageControl::getInstance()->setCurrentPage(TrainingPage_E);
}

