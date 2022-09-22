#include "gamedisplaypage.h"
#include "ui_gamedisplaypage.h"

GameDisplayPage::GameDisplayPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameDisplayPage)
{
    ui->setupUi(this);
}

GameDisplayPage::~GameDisplayPage()
{
    delete ui;
}
