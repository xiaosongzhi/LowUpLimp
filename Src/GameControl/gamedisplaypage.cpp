#include "gamedisplaypage.h"
#include "ui_gamedisplaypage.h"
#include <QPropertyAnimation>
#include <QDebug>
GameDisplayPage::GameDisplayPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameDisplayPage),
    m_openState(true)
{
    ui->setupUi(this);
    m_leftAnimation = new QPropertyAnimation(ui->leftPage_GroupBox,"pos");
    m_rightAnimation = new QPropertyAnimation(ui->rightPage_GroupBox,"pos");
    m_leftAnimation->setDuration(1000);
    m_rightAnimation->setDuration(1000);

}

GameDisplayPage::~GameDisplayPage()
{
    delete ui;
}

void GameDisplayPage::on_start_Btn_clicked()
{
    m_leftAnimation->start(QAbstractAnimation::KeepWhenStopped);
}

void GameDisplayPage::open_Btn_clicked()
{
    m_leftAnimation->setStartValue(QPoint(-360,0));
    m_leftAnimation->setEndValue(QPoint(0,0));
    m_rightAnimation->setStartValue(QPoint(1920,0));
    m_rightAnimation->setEndValue(QPoint(1560,0));
    m_leftAnimation->start(QAbstractAnimation::KeepWhenStopped);
    m_rightAnimation->start(QAbstractAnimation::KeepWhenStopped);
}

void GameDisplayPage::close_Btn_clicked()
{
    m_leftAnimation->setStartValue(QPoint(0,0));
    m_leftAnimation->setEndValue(QPoint(-360,0));
    m_rightAnimation->setStartValue(QPoint(1560,0));
    m_rightAnimation->setEndValue(QPoint(1920,0));
    m_leftAnimation->start(QAbstractAnimation::KeepWhenStopped);
    m_rightAnimation->start(QAbstractAnimation::KeepWhenStopped);
}

void GameDisplayPage::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    if(m_openState)
        close_Btn_clicked();
    else
        open_Btn_clicked();
    m_openState = !m_openState;
}



