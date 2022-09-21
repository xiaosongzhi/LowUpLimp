#include "spasmtipsdialog.h"
#include "ui_spasmtipsdialog.h"

SpasmTipsDialog::SpasmTipsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpasmTipsDialog)
{
    ui->setupUi(this);
}

SpasmTipsDialog::~SpasmTipsDialog()
{
    delete ui;
}
