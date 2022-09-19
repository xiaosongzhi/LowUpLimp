#ifndef FESPARAMBTN_H
#define FESPARAMBTN_H

#include <QWidget>

namespace Ui {
class FesParamBtn;
}

class FesParamBtn : public QWidget
{
    Q_OBJECT

public:
    explicit FesParamBtn(QWidget *parent = nullptr);
    ~FesParamBtn();

    void initButton(QString title,QString unit);

    void setData(int data);

signals:
    void buttonClicked();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
private:
    Ui::FesParamBtn *ui;
};

#endif // FESPARAMBTN_H
