#include "fesparamset.h"
#include "ui_fesparamset.h"

FesParamSet::FesParamSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FesParamSet)
{
    ui->setupUi(this);
}

FesParamSet::~FesParamSet()
{
    delete ui;
}
