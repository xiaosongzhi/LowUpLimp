#include "armorleg.h"
#include "ui_armorleg.h"

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
