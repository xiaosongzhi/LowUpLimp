#ifndef EMERGENCYSTOPDIALOG_H
#define EMERGENCYSTOPDIALOG_H

#include <QDialog>
#include <QSound>
namespace Ui {
class EmergencyStopDialog;
}

class EmergencyStopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmergencyStopDialog(QWidget *parent = nullptr);
    ~EmergencyStopDialog();

    //痉挛报警音控制
    void playBell();
    //停止报警音
    void stopPlayBell();
protected:
    void paintEvent(QPaintEvent *event);

    void showEvent(QShowEvent *event);

    void closeEvent(QCloseEvent *event);
private slots:
    void on_emergency_Btn_clicked();

private:
    Ui::EmergencyStopDialog *ui;
    QSound bells;       //铃声对象
};

#endif // EMERGENCYSTOPDIALOG_H
