#include "fesparambtn.h"
#include "ui_fesparambtn.h"
#include <QMouseEvent>
FesParamBtn::FesParamBtn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FesParamBtn)
{
    ui->setupUi(this);
}

FesParamBtn::~FesParamBtn()
{
    delete ui;
}

void FesParamBtn::initButton(QString title,QString unit)
{
    ui->title_Label->setText(title);
    ui->unit_Label->setText(unit);
}

void FesParamBtn::setData(int data)
{
    ui->data_Label->setText(QString::number(data));
}

void FesParamBtn::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit buttonClicked();
}

int FesParamBtn::getValue()
{
    m_value = ui->data_Label->text().toInt();
    return m_value;
}
