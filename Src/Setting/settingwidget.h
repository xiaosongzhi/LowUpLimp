#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QButtonGroup>
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

private:
    Ui::SettingWidget *ui;
    QButtonGroup *m_buttonGroup;
};

#endif // SETTINGWIDGET_H
