#include "titlewidget.h"
#include "ui_titlewidget.h"
#include <QPixmap>
TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);
}

TitleWidget::~TitleWidget()
{
    delete ui;
}

void TitleWidget::on_reback_Btn_clicked()
{

}
//设置当前用户
void TitleWidget::setUser(const ST_PatientMsg& st_patientMsg)
{
    ui->name_Label->setText(st_patientMsg.name);
    QPixmap pixmap;
    QString sexPath;
    switch(st_patientMsg.sex)
    {
    case 0:
        sexPath = "";
        break;
    case 1:
        sexPath = "";
        break;
    }
    pixmap.load(sexPath);
    ui->sex_Label->setPixmap(pixmap);
}
//设置wifi信号强度
void TitleWidget::setSignalStrength(int value)
{

}
//设置标题
void TitleWidget::setTitle(QString title)
{
    ui->title_Label->setText(title);
}
