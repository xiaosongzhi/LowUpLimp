#include "quitgamedialog.h"
#include "ui_quitgamedialog.h"
#include <QPainter>
QuitGameDialog::QuitGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuitGameDialog),
    m_result(0)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);
}

QuitGameDialog::~QuitGameDialog()
{
    delete ui;
}

int QuitGameDialog::getResult()
{
    return m_result;
}

void QuitGameDialog::on_cancel_Btn_clicked()
{
    m_result = 0;
    this->close();
}


void QuitGameDialog::on_confirm_Btn_clicked()
{
    m_result = 1;
    this->close();
}

void QuitGameDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
