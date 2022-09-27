#ifndef ADVANCEDDIALOG_H
#define ADVANCEDDIALOG_H
#include "dataformate.h"
#include <QDialog>

namespace Ui {
class AdvancedDialog;
}

class AdvancedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdvancedDialog(QWidget *parent = nullptr);
    ~AdvancedDialog();

    ST_AdvancedParam getValue();

protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_confirm_Btn_clicked();

    void on_cancel_Btn_clicked();

    void on_skipPassive_Btn_clicked();

    void on_preheatFesSwitch_Btn_clicked();

private:
    Ui::AdvancedDialog *ui;
    bool fesSwitchFlag;     //是否启动电刺激
    bool isSkipPassive;     //是否跳过此阶段
    ST_AdvancedParam st_advanceParam;
};

#endif // ADVANCEDDIALOG_H
