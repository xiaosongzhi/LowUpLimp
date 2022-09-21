#include "selectuserdialog.h"
#include "ui_selectuserdialog.h"

SelectUserDialog::SelectUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectUserDialog)
{
    ui->setupUi(this);
}

SelectUserDialog::~SelectUserDialog()
{
    delete ui;
}

void SelectUserDialog::on_cancel_Btn_clicked()
{

}


void SelectUserDialog::on_confirm_Btn_clicked()
{

}

