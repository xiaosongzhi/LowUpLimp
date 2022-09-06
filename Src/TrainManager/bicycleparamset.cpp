#include "bicycleparamset.h"
#include "ui_bicycleparamset.h"

BicycleParamSet::BicycleParamSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BicycleParamSet)
{
    ui->setupUi(this);
}

BicycleParamSet::~BicycleParamSet()
{
    delete ui;
}
