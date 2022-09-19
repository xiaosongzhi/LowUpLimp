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

