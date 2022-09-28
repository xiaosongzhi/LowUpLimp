#include "selectuserdialog.h"
#include "ui_selectuserdialog.h"
#include <QPainter>
SelectUserDialog::SelectUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectUserDialog),
    isSelectedUser(false)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);
}

SelectUserDialog::~SelectUserDialog()
{
    delete ui;
}

void SelectUserDialog::setUserMsg(const ST_PatientMsg& userMsg)
{
    QString userMessage;
    QString sex;
    if(0 == userMsg.sex)
        sex = tr("男");
    else if(1 == userMsg.sex)
        sex = tr("女");
    userMessage = userMsg.name  + "  " + sex + "  " + QString::number(userMsg.ID);
    ui->userMessage_Label->setText(userMessage);
}

bool SelectUserDialog::isSelectUser()
{
    return isSelectedUser;
}

void SelectUserDialog::on_cancel_Btn_clicked()
{
    isSelectedUser = false;
    this->close();
}


void SelectUserDialog::on_confirm_Btn_clicked()
{
    isSelectedUser = true;
    this->close();
}

void SelectUserDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
