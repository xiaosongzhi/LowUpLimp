#ifndef ARMORLEG_H
#define ARMORLEG_H

#include <QWidget>
#include <QSound>
class AdvancedDialog;
namespace Ui {
class ArmOrLeg;
}

class ArmOrLeg : public QWidget
{
    Q_OBJECT

public:
    explicit ArmOrLeg(QWidget *parent = nullptr);
    ~ArmOrLeg();

    /*****设置训练类型****
     * 参数@int8_t type 0-单踏车 1-FES踏车
     * *****/
    void setTrainType(int8_t type);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_upDownLimp_RadioButton_toggled(bool checked);

    void on_advanced1_Btn_clicked();

    void on_upAdvanced2_Btn_clicked();

    void on_downAdvanced2_Btn_clicked();

    void on_next_Btn_clicked();

    void on_confirm_Btn_clicked();

    void on_spasmClose2_RadioButton_toggled(bool checked);

    void on_spasmClose1_RadioButton_toggled(bool checked);

    void on_test_Btn_clicked();

private:
    void initWidget();

private:
    Ui::ArmOrLeg *ui;
    AdvancedDialog *m_advanceDialog;

};

#endif // ARMORLEG_H
