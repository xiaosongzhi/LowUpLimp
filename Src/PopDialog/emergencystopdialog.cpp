#include "emergencystopdialog.h"
#include "ui_emergencystopdialog.h"
#include <QPainter>
#include <QDebug>
EmergencyStopDialog::EmergencyStopDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmergencyStopDialog),
    bells("./DependFile/Music/emergency.wav")
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);    //设置透明

    //设置报警音无线循环
    bells.setLoops(-1);
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

void EmergencyStopDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    playBell();
}

void EmergencyStopDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    stopPlayBell();
}

void EmergencyStopDialog::on_emergency_Btn_clicked()
{
    static int closeTime;
    closeTime++;
    if(closeTime > 30)
    {
        closeTime = 0;
        this->close();
    }
    this->close();
}

//痉挛报警音控制
void EmergencyStopDialog::playBell()
{
    bells.play();
}
//停止报警音
void EmergencyStopDialog::stopPlayBell()
{
    if(bells.loopsRemaining())
        bells.stop();
}
