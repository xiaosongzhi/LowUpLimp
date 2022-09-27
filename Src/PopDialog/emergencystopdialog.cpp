#include "emergencystopdialog.h"
#include "ui_emergencystopdialog.h"
#include <QPainter>
EmergencyStopDialog::EmergencyStopDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmergencyStopDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);    //设置透明
}

EmergencyStopDialog::~EmergencyStopDialog()
{
    delete ui;
}

void EmergencyStopDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
