#include "selectuserdialog.h"
#include "ui_selectuserdialog.h"
#include <QPainter>
SelectUserDialog::SelectUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectUserDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);
}

SelectUserDialog::~SelectUserDialog()
{
    delete ui;
}

void SelectUserDialog::on_cancel_Btn_clicked()
{
    this->close();
}


void SelectUserDialog::on_confirm_Btn_clicked()
{
    this->close();
}

void SelectUserDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
