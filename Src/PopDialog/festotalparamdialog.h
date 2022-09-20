#ifndef FESTOTALPARAMDIALOG_H
#define FESTOTALPARAMDIALOG_H

#include <QDialog>

namespace Ui {
class FesTotalParamDialog;
}

class FesTotalParamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FesTotalParamDialog(QWidget *parent = nullptr);
    ~FesTotalParamDialog();

    void setTitleAndUnit(QString title,QString unit);

    int getValue();

    void setValue(int value);
private slots:
    void on_cancel_Btn_clicked();

    void on_confirm_Btn_clicked();

    void on_minus_Btn_clicked();

    void on_plus_Btn_clicked();

    void on_slider_valueChanged(int value);

private:
    Ui::FesTotalParamDialog *ui;

    int m_value;
};

#endif // FESTOTALPARAMDIALOG_H
