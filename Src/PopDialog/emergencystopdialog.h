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
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_emergency_Btn_clicked();

private:
    Ui::EmergencyStopDialog *ui;
};

#endif // EMERGENCYSTOPDIALOG_H
