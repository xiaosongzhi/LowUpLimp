#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include "dbforrmate.h"
namespace Ui {
class TitleWidget;
}

class TitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TitleWidget(QWidget *parent = nullptr);
    ~TitleWidget();

    //设置当前用户
    void setUser(const ST_PatientMsg&);
    //设置wifi信号强度
    void setSignalStrength(int value);
    //设置标题
    void setTitle(QString);
private slots:


    void slotBackClicked();
private:
    Ui::TitleWidget *ui;
};

#endif // TITLEWIDGET_H
