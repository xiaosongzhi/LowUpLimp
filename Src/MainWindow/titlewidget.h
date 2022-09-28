#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include "dbforrmate.h"
#include "dataformate.h"
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
    void setTitleByPage(E_PAGENAME);

    //设置界面从属状态
    /*****设置训练类型****
     * 参数@int8_t type 0-单踏车 1-FES踏车
     * *****/
    void setTrainType(int8_t type);

    void  setBackBtnVisible(bool);
private slots:

    void slotBackClicked();
    void on_user_Btn_clicked();

private:
    Ui::TitleWidget *ui;
    int8_t m_trainType;
};

#endif // TITLEWIDGET_H
