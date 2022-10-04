#include "deleteuserdialog.h"
#include "ui_deleteuserdialog.h"
#include <QPainter>
#include <QPaintEvent>
DeleteUserDialog::DeleteUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteUserDialog),
    m_isdeleted(false)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);    //设置透明

}

DeleteUserDialog::~DeleteUserDialog()
{
    delete ui;
}

bool DeleteUserDialog::isDeletedUser()
{
    return m_isdeleted;
}

void DeleteUserDialog::on_cancel_Btn_clicked()
{
    m_isdeleted = false;
    this->close();
}


void DeleteUserDialog::on_confirm_Btn_clicked()
{
    m_isdeleted = true;
    this->close();
}

void DeleteUserDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
