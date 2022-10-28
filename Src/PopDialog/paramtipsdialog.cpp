#include "paramtipsdialog.h"
#include "ui_paramtipsdialog.h"
#include <QPainter>
ParamTipsDialog::ParamTipsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamTipsDialog)
    ,m_result(0)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);
}

ParamTipsDialog::~ParamTipsDialog()
{
    delete ui;
}

int ParamTipsDialog::getResult()
{
    return m_result;
}

void ParamTipsDialog::setParamTipsMsg(QString msg)
{
    ui->tipMsg_Label->setText(msg);
}

void ParamTipsDialog::on_cancel_Btn_clicked()
{
    m_result = 0;
    this->close();
}


void ParamTipsDialog::on_confirm_Btn_clicked()
{
    m_result = 1;
    this->close();
}

void ParamTipsDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
