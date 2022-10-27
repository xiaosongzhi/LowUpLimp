#include "spasmtipsdialog.h"
#include "ui_spasmtipsdialog.h"
#include <QPainter>
#include "ccommunicateapi.h"
SpasmTipsDialog::SpasmTipsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpasmTipsDialog),
    bells("./DependFile/Music/spasmTips.wav")
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);

    //设置报警音无线循环
    bells.setLoops(-1);
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
    playBell();
    ui->tips_Label->setText(tipsMsg);
    this->exec();
}

void SpasmTipsDialog::setSpasmCompletedDirection(int8_t direction)
{
    m_direction = direction;
}

void SpasmTipsDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}

void SpasmTipsDialog::on_confirm_Btn_clicked()
{
    stopPlayBell();
    CCommunicateAPI::getInstance()->sendRealTimeParam(SPASM_CONFIRM,m_direction);
    this->close();
}

//痉挛报警音控制
void SpasmTipsDialog::playBell()
{
    bells.play();
}
//停止报警音
void SpasmTipsDialog::stopPlayBell()
{
    if(bells.loopsRemaining())
        bells.stop();
}
