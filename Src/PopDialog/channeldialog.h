#ifndef CHANNELDIALOG_H
#define CHANNELDIALOG_H
/*********
 * Fes参数界面下方刺激盒中按钮弹出的对话框
 * ****/
#include <QDialog>
#include <QButtonGroup>
#include "dataformate.h"
namespace Ui {
class ChannelDialog;
}

class ChannelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChannelDialog(QWidget *parent = nullptr);
    ~ChannelDialog();
    void initWidget();

    void setTitle(QString title);

    ST_MuscleParam getValue();

    void setMuscleState(QList<bool>);

protected:
    void paintEvent(QPaintEvent *event);

//    void showEvent(QShowEvent *event);

private slots:
    void on_confirm_Btn_clicked();

    void on_frequentMinus_Btn_clicked();

    void on_frequentPlus_Btn_clicked();

    void on_frequent_Slider_valueChanged(int value);

    void on_PWMMinus_Btn_clicked();

    void on_PWMPlus_Btn_clicked();

    void on_plus_Slider_valueChanged(int value);

    void on_minCurrentMinus_Btn_clicked();

    void on_minCurrentPlus_Btn_clicked();

    void on_minCurrent_Slider_valueChanged(int value);

    void on_maxCurrentMinus_Btn_clicked();

    void on_maxCurrentPlus_Btn_clicked();

    void on_maxCurrent_Slider_valueChanged(int value);

    void on_switch_Btn_clicked();

    void slotButtonClicked(int);

    void slotButtonClicked(QAbstractButton*);

private:
    Ui::ChannelDialog *ui;
    QButtonGroup *m_buttonGroup;
    ST_MuscleParam st_MuscleParam;
};

#endif // CHANNELDIALOG_H
