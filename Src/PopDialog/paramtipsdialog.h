#ifndef PARAMTIPSDIALOG_H
#define PARAMTIPSDIALOG_H

#include <QDialog>

namespace Ui {
class ParamTipsDialog;
}

class ParamTipsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParamTipsDialog(QWidget *parent = nullptr);
    ~ParamTipsDialog();
    int getResult();
    void setParamTipsMsg(QString msg);
private slots:
    void on_cancel_Btn_clicked();

    void on_confirm_Btn_clicked();
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::ParamTipsDialog *ui;
    int m_result;
};

#endif // PARAMTIPSDIALOG_H
