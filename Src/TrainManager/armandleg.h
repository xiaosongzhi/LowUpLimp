#ifndef ARMANDLEG_H
#define ARMANDLEG_H

#include <QWidget>

namespace Ui {
class ArmAndLeg;
}

class ArmAndLeg : public QWidget
{
    Q_OBJECT

public:
    explicit ArmAndLeg(QWidget *parent = nullptr);
    ~ArmAndLeg();

private:
    Ui::ArmAndLeg *ui;
};

#endif // ARMANDLEG_H
