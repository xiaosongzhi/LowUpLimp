#include "passworddialog.h"
#include "ui_passworddialog.h"
#include <QPainter>
#include <QDebug>
PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);
    setAttribute(Qt::WA_DeleteOnClose);
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}

void PasswordDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}

void PasswordDialog::on_confirm_Btn_clicked()
{
    this->close();
}

