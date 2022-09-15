#include "fessetting.h"
#include "ui_fessetting.h"

FesSetting::FesSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FesSetting)
{
    ui->setupUi(this);
}

FesSetting::~FesSetting()
{
    delete ui;
}
