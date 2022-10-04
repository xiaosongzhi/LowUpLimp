#include "spasmtipsdialog.h"
#include "ui_spasmtipsdialog.h"
#include <QPainter>
SpasmTipsDialog::SpasmTipsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpasmTipsDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);
    setAttribute(Qt::WA_DeleteOnClose);
}

SpasmTipsDialog::~SpasmTipsDialog()
{
    delete ui;
}

void SpasmTipsDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}

void SpasmTipsDialog::on_confirm_Btn_clicked()
{
    this->close();
}

