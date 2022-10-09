#include "musclebutton.h"
#include "ui_musclebutton.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>

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
        limpFlag = ":/DependFile/Source/channel/left.png";
    else
        limpFlag = ":/DependFile/Source/channel/right.png";
    QPixmap pixmap;
    pixmap.load(limpFlag);
    ui->Image_Label->setPixmap(pixmap);
    ui->muscle_Label->setText(param.muscleName );
    ui->current_Label->setText(QString::number(param.minCurrent)+"~"+QString::number(param.maxCurrent) + "mA");
    ui->plus_Label->setText(QString::number(param.plus) + "us");
    ui->frequency_Label->setText(QString::number(param.frequency) + "Hz");

    st_muscleParam = param;
}

void MuscleButton::initWidget(QString title,int id)
{
    ui->channel_Label->setText(title);
    m_id = id;
}

void MuscleButton::setMuscleEnabled(bool enabled)
{
    QString enabledStyle = "#groupBox{background: #E4F4FC;"
                           "border-radius: 6px;}";
    QString disenabledStyle = "#groupBox{background: #EFEFEF;border-radius: 6px;}";
    if(enabled)
        ui->groupBox->setStyleSheet(enabledStyle);
    else
        ui->groupBox->setStyleSheet(disenabledStyle);
}

ST_MuscleParam MuscleButton::getMuscleParam()
{
    return st_muscleParam;
}
