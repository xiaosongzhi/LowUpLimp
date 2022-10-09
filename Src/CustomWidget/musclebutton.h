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

    void initWidget(QString title,int id);

    void setMuscleEnabled(bool);

    ST_MuscleParam getMuscleParam();
signals:
    void buttonClicked(int id);

protected:
    virtual void paintEvent(QPaintEvent *event);

    virtual void mousePressEvent(QMouseEvent *event);
private:
    Ui::MuscleButton *ui;
    int m_id;
    ST_MuscleParam st_muscleParam;
};

#endif // MUSCLEBUTTON_H
