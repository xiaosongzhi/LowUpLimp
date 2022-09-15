#include "armandleg.h"
#include "ui_armandleg.h"

ArmAndLeg::ArmAndLeg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmAndLeg)
{
    ui->setupUi(this);
}

ArmAndLeg::~ArmAndLeg()
{
    delete ui;
}
