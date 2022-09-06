#ifndef BICYCLEPARAMSET_H
#define BICYCLEPARAMSET_H

#include <QWidget>

namespace Ui {
class BicycleParamSet;
}

class BicycleParamSet : public QWidget
{
    Q_OBJECT

public:
    explicit BicycleParamSet(QWidget *parent = nullptr);
    ~BicycleParamSet();

private:
    Ui::BicycleParamSet *ui;
};

#endif // BICYCLEPARAMSET_H
