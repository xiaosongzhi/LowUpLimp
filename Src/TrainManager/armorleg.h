#ifndef ARMORLEG_H
#define ARMORLEG_H

#include <QWidget>

namespace Ui {
class ArmOrLeg;
}

class ArmOrLeg : public QWidget
{
    Q_OBJECT

public:
    explicit ArmOrLeg(QWidget *parent = nullptr);
    ~ArmOrLeg();

private slots:
    void on_upDownLimp_RadioButton_toggled(bool checked);

private:
    Ui::ArmOrLeg *ui;
};

#endif // ARMORLEG_H
