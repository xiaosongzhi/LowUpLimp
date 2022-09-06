#ifndef FESPARAMSET_H
#define FESPARAMSET_H

#include <QWidget>

namespace Ui {
class FesParamSet;
}

class FesParamSet : public QWidget
{
    Q_OBJECT

public:
    explicit FesParamSet(QWidget *parent = nullptr);
    ~FesParamSet();

private:
    Ui::FesParamSet *ui;
};

#endif // FESPARAMSET_H
