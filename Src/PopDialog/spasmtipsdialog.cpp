#include "spasmtipsdialog.h"
#include "ui_spasmtipsdialog.h"
#include <QPainter>
#include "ccommunicateapi.h"
SpasmTipsDialog::SpasmTipsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpasmTipsDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);
}

SpasmTipsDialog::~SpasmTipsDialog()
{
    delete ui;
}

void SpasmTipsDialog::setSpasmDialogVisible(bool isVisable, int times)
{
    Q_UNUSED(isVisable)
    QString tipsMsg;
    switch(times)
    {
    case 1:
        tipsMsg = tr("请注意发生1次痉挛!");
        break;
    case 2:
         tipsMsg = tr("请注意发生2次痉挛!");
        break;
    case 3:
        tipsMsg = tr("请注意发生3次痉挛,训练将停止!");
        break;
    }

    ui->tips_Label->setText(tipsMsg);
    this->exec();
}

void SpasmTipsDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}

void SpasmTipsDialog::on_confirm_Btn_clicked()
{
    CCommunicateAPI::getInstance()->sendRealTimeParam(SPASM_CONFIRM,0);
    this->close();
}

