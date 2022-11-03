#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QTimer>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

private slots:
    void on_FESA_Btn_clicked();

    void on_resetPassword_Btn_clicked();

    void on_FESB_Btn_clicked();

    void on_bioelectricity_Btn_clicked();

    void on_systemSetting_Btn_clicked();

    void on_secretManage_Btn_clicked();

    void on_productMsg_Btn_clicked();

    void on_cancelPassword_Btn_clicked();

    void on_savePassword_Btn_clicked();

    void on_CH_RadioButton_clicked();

    void on_EN_RadioButton_clicked();

    void slotCheckTimerSlot();
    void on_reset_Btn_clicked();

private:
    void initWidget();
private:
    Ui::SettingWidget *ui;
    QButtonGroup *m_buttonGroup;
    QTimer *checkTimer;
    bool fesAState,fesBState,bioelectricityState;
};

#endif // SETTINGWIDGET_H
