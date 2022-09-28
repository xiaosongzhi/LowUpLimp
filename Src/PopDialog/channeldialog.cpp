#include "channeldialog.h"
#include "ui_channeldialog.h"
#include <QDebug>
#include <QPainter>
ChannelDialog::ChannelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChannelDialog),
    m_buttonGroup(nullptr)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);    //设置透明
    initWidget();
}

ChannelDialog::~ChannelDialog()
{
    delete ui;
}

void ChannelDialog::initWidget()
{
    //设置按钮互斥,配合样式表
    m_buttonGroup = new QButtonGroup;
//    m_buttonGroup->setExclusive(true);
    m_buttonGroup->addButton(ui->gongErL_Btn,1);
    m_buttonGroup->addButton(ui->gongSanL_Btn,2);
    m_buttonGroup->addButton(ui->qianSanJiaoL_Btn,3);
    m_buttonGroup->addButton(ui->houSanJiaoL_Btn,4);
    m_buttonGroup->addButton(ui->quWanL_Btn,5);
    m_buttonGroup->addButton(ui->shenWanL_Btn,6);
    m_buttonGroup->addButton(ui->jianJiaL_Btn,7);
    m_buttonGroup->addButton(ui->gangShangL_Btn,8);
    m_buttonGroup->addButton(ui->guoShengL_Btn,9);
    m_buttonGroup->addButton(ui->tunDaL_Btn,10);
    m_buttonGroup->addButton(ui->jingQianL_Btn,11);
    m_buttonGroup->addButton(ui->feiChangL_Btn,12);
    m_buttonGroup->addButton(ui->fuJiL_Btn,13);
    m_buttonGroup->addButton(ui->shuJiL_Btn,14);
    m_buttonGroup->addButton(ui->guSiTouL_Btn,15);

    m_buttonGroup->addButton(ui->gongErR_Btn,16);
    m_buttonGroup->addButton(ui->gongSanR_Btn,17);
    m_buttonGroup->addButton(ui->qianSanJiaoR_Btn,18);
    m_buttonGroup->addButton(ui->houSanJiaoR_Btn,19);
    m_buttonGroup->addButton(ui->quWanR_Btn,20);
    m_buttonGroup->addButton(ui->shenWanR_Btn,21);
    m_buttonGroup->addButton(ui->jianJiaR_Btn,22);
    m_buttonGroup->addButton(ui->gangShangR_Btn,23);
    m_buttonGroup->addButton(ui->guoShengR_Btn,24);
    m_buttonGroup->addButton(ui->tunDaR_Btn,25);
    m_buttonGroup->addButton(ui->jingQianR_Btn,26);
    m_buttonGroup->addButton(ui->feiChangR_Btn,27);
    m_buttonGroup->addButton(ui->fuJiR_Btn,28);
    m_buttonGroup->addButton(ui->shuJiR_Btn,29);
    m_buttonGroup->addButton(ui->guSiTouR_Btn,30);

    foreach(QAbstractButton *button,m_buttonGroup->buttons())
        button->setCheckable(true);

    connect(m_buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(slotButtonClicked(int)));
    connect(m_buttonGroup,SIGNAL(buttonClicked(QAbstractButton *)),this,SLOT(slotButtonClicked(QAbstractButton*)));

}

void ChannelDialog::setTitle(QString title)
{
    ui->channelName_Label->setText(title);
}

ST_MuscleParam ChannelDialog::getValue()
{
    return st_MuscleParam;
}

void ChannelDialog::on_confirm_Btn_clicked()
{
    st_MuscleParam.plus = ui->plus_Label->text().toInt();
    st_MuscleParam.minCurrent = ui->minCurrent_Label->text().toInt();
    st_MuscleParam.frequency = ui->frequent_Label->text().toInt();
    st_MuscleParam.maxCurrent = ui->maxCurrent_Label->text().toInt();

    this->close();
}

void ChannelDialog::slotButtonClicked(int id)
{
    st_MuscleParam.muscleId = id;
}

void ChannelDialog::slotButtonClicked(QAbstractButton *button)
{
    st_MuscleParam.muscleName = button->text();
    QString muscleName = button->objectName();
    int index = muscleName.indexOf("_");

    QPixmap pixmap;
    QString fileName("./DependFile/Image/leftMuscle/");
    fileName.append(muscleName.leftRef(index-1));
    fileName.append(".png");
    pixmap.load(fileName );
    //F:\GitRepository\UpperLowerLimp\UpLowLimp\DependFile\Image\leftMuscle
    ui->muscleImage_Label->setPixmap(pixmap);
}

void ChannelDialog::on_frequentMinus_Btn_clicked()
{
    int value = ui->frequent_Slider->value();
    --value;
    ui->frequent_Slider->setValue(value);
}

void ChannelDialog::on_frequentPlus_Btn_clicked()
{
    int value = ui->frequent_Slider->value();
    ++value;
    ui->frequent_Slider->setValue(value);
}

void ChannelDialog::on_frequent_Slider_valueChanged(int value)
{
    ui->frequent_Label->setText(QString::number(value));
}

void ChannelDialog::on_PWMMinus_Btn_clicked()
{
    int value = ui->plus_Slider->value();
    --value;
    ui->plus_Slider->setValue(value);
}

void ChannelDialog::on_PWMPlus_Btn_clicked()
{
    int value = ui->plus_Slider->value();
    ++value;
    ui->plus_Slider->setValue(value);
}

void ChannelDialog::on_plus_Slider_valueChanged(int value)
{
    ui->plus_Label->setText(QString::number(value));
}

void ChannelDialog::on_minCurrentMinus_Btn_clicked()
{
    int value = ui->minCurrent_Slider->value();
    --value;
    ui->minCurrent_Slider->setValue(value);
}

void ChannelDialog::on_minCurrentPlus_Btn_clicked()
{
    int value = ui->minCurrent_Slider->value();
    ++value;
    ui->minCurrent_Slider->setValue(value);
}

void ChannelDialog::on_minCurrent_Slider_valueChanged(int value)
{
    ui->minCurrent_Label->setText(QString::number(value));
}

void ChannelDialog::on_maxCurrentMinus_Btn_clicked()
{
    int value = ui->maxCurrent_Slider->value();
    --value;
    ui->maxCurrent_Slider->setValue(value);
}

void ChannelDialog::on_maxCurrentPlus_Btn_clicked()
{
    int value = ui->maxCurrent_Slider->value();
    ++value;
    ui->maxCurrent_Slider->setValue(value);
}

void ChannelDialog::on_maxCurrent_Slider_valueChanged(int value)
{
    ui->maxCurrent_Label->setText(QString::number(value));
}

void ChannelDialog::on_switch_Btn_clicked()
{
    if(ui->switch_Btn->styleSheet() == "border-image: url(:/DependFile/Source/gamePage/switchOn.png);")
    {
        ui->switch_Btn->setStyleSheet("border-image: url(:/DependFile/Source/gamePage/switchOff.png);");
        st_MuscleParam.connectState = false;
    }
    else if(ui->switch_Btn->styleSheet() == "border-image: url(:/DependFile/Source/gamePage/switchOff.png);")
    {
        st_MuscleParam.connectState = true;
        ui->switch_Btn->setStyleSheet("border-image: url(:/DependFile/Source/gamePage/switchOn.png);");
    }

}

void ChannelDialog::setMuscleState(QList<bool> muscleStateList)
{
    foreach(QAbstractButton *button,m_buttonGroup->buttons())
    {
        QPushButton* pushButton = dynamic_cast<QPushButton*>(button);
        int id = m_buttonGroup->id(button);
        pushButton->setEnabled(muscleStateList.at(id-1));
    }
}

void ChannelDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
