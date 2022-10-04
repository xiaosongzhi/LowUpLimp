#include "festipsdialog.h"
#include "ui_festipsdialog.h"
#include <QPainter>
FesTipsDialog::FesTipsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FesTipsDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);

}

FesTipsDialog::~FesTipsDialog()
{
    delete ui;
}

void FesTipsDialog::on_confirm_Btn_clicked()
{
    this->close();
}

void FesTipsDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
