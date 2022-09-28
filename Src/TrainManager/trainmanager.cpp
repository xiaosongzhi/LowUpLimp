#include "trainmanager.h"
#include "ui_trainmanager.h"
#include "mainwindowpagecontrol.h"
#include <QDebug>
TrainManager::TrainManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainManager)
{
    ui->setupUi(this);
}

TrainManager::~TrainManager()
{
    delete ui;
}

void TrainManager::on_bicycleTrain_Btn_clicked()
{
    MainWindowPageControl::getInstance()->setCurrentPage(BicycleParamSet_E);
}

void TrainManager::on_fesBicycleTrain_Btn_clicked()
{
    qDebug()<<"fesBicycle";
    //先踏车设置 后FES
    MainWindowPageControl::getInstance()->setCurrentPage(FesBicycleParamSet_E);
}


void TrainManager::on_fesTrain_Btn_clicked()
{
    MainWindowPageControl::getInstance()->setCurrentPage(FesParamSet_E);
}


void TrainManager::on_setting_Btn_clicked()
{
    MainWindowPageControl::getInstance()->setCurrentPage(SettingPage_E);
}




