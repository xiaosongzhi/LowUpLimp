#include "deleteuserdialog.h"
#include "ui_deleteuserdialog.h"
#include <QPainter>
#include <QPaintEvent>
DeleteUserDialog::DeleteUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteUserDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);    //设置透明
}

DeleteUserDialog::~DeleteUserDialog()
{
    delete ui;
}

void DeleteUserDialog::on_cancel_Btn_clicked()
{
    this->close();
}


void DeleteUserDialog::on_confirm_Btn_clicked()
{
    this->close();
}

void DeleteUserDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
