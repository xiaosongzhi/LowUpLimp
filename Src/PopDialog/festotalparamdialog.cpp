#include "festotalparamdialog.h"
#include "ui_festotalparamdialog.h"
#include <QPainter>
FesTotalParamDialog::FesTotalParamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FesTotalParamDialog),
    m_value(0)
{
    ui->setupUi(this);
}

FesTotalParamDialog::~FesTotalParamDialog()
{
    delete ui;
}

void FesTotalParamDialog::setTitleAndUnit(QString title, QString unit)
{
    ui->title_Label->setText(title);
    ui->unit_Label->setText(unit);
}

int FesTotalParamDialog::getValue()
{
    return m_value;
}

void FesTotalParamDialog::setValue(int value)
{
    ui->slider->setValue(value);
}

void FesTotalParamDialog::on_cancel_Btn_clicked()
{
    this->close();
}

void FesTotalParamDialog::on_confirm_Btn_clicked()
{
    m_value = ui->value_Label->text().toInt();
    this->close();
}

void FesTotalParamDialog::on_minus_Btn_clicked()
{
    int value = ui->slider->value();
    --value;
    ui->slider->setValue(value);
}

void FesTotalParamDialog::on_plus_Btn_clicked()
{
    int value = ui->slider->value();
    ++value;
    ui->slider->setValue(value);
}

void FesTotalParamDialog::on_slider_valueChanged(int value)
{
    ui->value_Label->setText(QString::number(value));
}

void FesTotalParamDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}



