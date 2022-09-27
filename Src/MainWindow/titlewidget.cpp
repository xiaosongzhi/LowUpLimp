#include "titlewidget.h"
#include "ui_titlewidget.h"
#include <QPixmap>
#include <QDebug>
TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);
    connect(ui->back1_Btn,SIGNAL(clicked()),this,SLOT(slotBackClicked()));
    connect(ui->back2_Btn,SIGNAL(clicked()),this,SLOT(slotBackClicked()));

    ui->user_Btn->setIcon(QIcon(":/DependFile/Source/User/user.png"));
    ui->user_Btn->setIconSize(QSize(50,50));

}

TitleWidget::~TitleWidget()
{
    delete ui;
}


void TitleWidget::slotBackClicked()
{

}
//设置当前用户
void TitleWidget::setUser(const ST_PatientMsg& st_patientMsg)
{

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

}
//设置wifi信号强度
void TitleWidget::setSignalStrength(int value)
{
    Q_UNUSED(value)
}
//设置标题
void TitleWidget::setTitle(QString title)
{
    ui->title_Label->setText(title);
}
