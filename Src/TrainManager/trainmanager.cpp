#include "trainmanager.h"
#include "ui_trainmanager.h"

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

}


void TrainManager::on_fesBicycleTrain_Btn_clicked()
{

}


void TrainManager::on_fesTrain_Btn_clicked()
{

}


void TrainManager::on_setting_Btn_clicked()
{

}


void TrainManager::on_userManager_Btn_clicked()
{

}

