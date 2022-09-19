#ifndef MUSCLEBUTTON_H
#define MUSCLEBUTTON_H

#include <QWidget>
#include "dataformate.h"
namespace Ui {
class MuscleButton;
}

class MuscleButton : public QWidget
{
    Q_OBJECT

public:
    explicit MuscleButton(QWidget *parent = nullptr);
    ~MuscleButton();

    void setMuscleParamButton(const ST_MuscleParam&);

    void initWidget(QString title);
signals:
    void buttonClicked();

protected:
    virtual void paintEvent(QPaintEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);
private:
    Ui::MuscleButton *ui;
};

#endif // MUSCLEBUTTON_H
