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

private:
    Ui::ArmOrLeg *ui;
};

#endif // ARMORLEG_H
