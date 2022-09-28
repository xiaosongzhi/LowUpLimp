#include "armorleg.h"
#include "ui_armorleg.h"
#include <QDebug>
ArmOrLeg::ArmOrLeg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmOrLeg)
{
    ui->setupUi(this);
}

ArmOrLeg::~ArmOrLeg()
{
    delete ui;
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

}

//四肢中的上肢
void ArmOrLeg::on_upAdvanced2_Btn_clicked()
{

}

//四肢中的下肢
void ArmOrLeg::on_downAdvanced2_Btn_clicked()
{

}
