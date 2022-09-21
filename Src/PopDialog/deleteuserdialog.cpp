#include "deleteuserdialog.h"
#include "ui_deleteuserdialog.h"

DeleteUserDialog::DeleteUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteUserDialog)
{
    ui->setupUi(this);
}

DeleteUserDialog::~DeleteUserDialog()
{
    delete ui;
}

void DeleteUserDialog::on_cancel_Btn_clicked()
{

}


void DeleteUserDialog::on_confirm_Btn_clicked()
{

}

