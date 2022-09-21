#ifndef EMERGENCYSTOPDIALOG_H
#define EMERGENCYSTOPDIALOG_H

#include <QDialog>

namespace Ui {
class EmergencyStopDialog;
}

class EmergencyStopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmergencyStopDialog(QWidget *parent = nullptr);
    ~EmergencyStopDialog();

private:
    Ui::EmergencyStopDialog *ui;
};

#endif // EMERGENCYSTOPDIALOG_H
