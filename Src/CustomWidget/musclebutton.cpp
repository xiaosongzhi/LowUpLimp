#include "musclebutton.h"
#include "ui_musclebutton.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QGraphicsDropShadowEffect>
MuscleButton::MuscleButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MuscleButton)
{
    ui->setupUi(this);
//    QGraphicsDropShadowEffect * shadowEffect = new QGraphicsDropShadowEffect();
//    shadowEffect->setYOffset(2);
//    shadowEffect->setBlurRadius(12);
//    shadowEffect->setColor(QColor(0,0,0,51));
//    this->setGraphicsEffect(shadowEffect);

}

MuscleButton::~MuscleButton()
{
    delete ui;
}

void MuscleButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
}

void MuscleButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    emit buttonClicked(m_id);
}

void MuscleButton::setMuscleParamButton(const ST_MuscleParam& param)
{
    QPixmap pix("");
    if(param.connectState)
        pix.load(":/DependFile/Source/signal/fesConnect.png");
    else
        pix.load(":/DependFile/Source/signal/fesDisconnect.png");
    ui->connectState_Label->setPixmap(pix);
    QString limpFlag;
    if(param.muscleId <= 15)
        limpFlag = tr("左");
    else
        limpFlag = tr("右");
    ui->muscle_Label->setText(param.muscleName + limpFlag);
    ui->current_Label->setText(QString::number(param.minCurrent)+"~"+QString::number(param.maxCurrent) + "mA");
    ui->plus_Label->setText(QString::number(param.plus) + "us");
    ui->frequency_Label->setText(QString::number(param.frequency) + "Hz");
}

void MuscleButton::initWidget(QString title,int id)
{
    ui->channel_Label->setText(title);
    m_id = id;
}
