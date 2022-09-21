#include "festipsdialog.h"
#include "ui_festipsdialog.h"

FesTipsDialog::FesTipsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FesTipsDialog)
{
    ui->setupUi(this);
}

FesTipsDialog::~FesTipsDialog()
{
    delete ui;
}

void FesTipsDialog::on_confirm_Btn_clicked()
{

}

