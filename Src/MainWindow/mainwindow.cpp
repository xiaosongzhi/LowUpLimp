#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->setView(new QListView());
//    ui->comboBox_2->setView(new QListView());
}

MainWindow::~MainWindow()
{
    delete ui;
}

