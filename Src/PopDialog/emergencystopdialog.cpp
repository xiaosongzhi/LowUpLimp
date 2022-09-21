#include "emergencystopdialog.h"
#include "ui_emergencystopdialog.h"

EmergencyStopDialog::EmergencyStopDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmergencyStopDialog)
{
    ui->setupUi(this);
}

EmergencyStopDialog::~EmergencyStopDialog()
{
    delete ui;
}
