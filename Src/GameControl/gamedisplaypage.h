#ifndef GAMEDISPLAYPAGE_H
#define GAMEDISPLAYPAGE_H

#include <QWidget>
#include <QLabel>
#include "dataformate.h"
#include "dbforrmate.h"
#include "spasmtipsdialog.h"
class QPropertyAnimation;
namespace Ui {
class GameDisplayPage;
}

class GameDisplayPage : public QWidget
{
    Q_OBJECT

public:
    explicit GameDisplayPage(QWidget *parent = nullptr);
    ~GameDisplayPage();


    //设置当前用户
    void setUser(const ST_PatientMsg&);
    //表头显示
    void setTitle();

    /****设置训练部位****
     * 参数@int type 0-上肢 1-下肢 2-上下肢
     * ***/
    void setTrainPart(int type);

    //填充电刺激参数
    void setChannelAData(int *data,int size);

    void setChannelBData(int *data,int size);

    //填充实时下位机反馈参数
    void setRealTimeParam(int updown,int remainTime,int speed,int power);

    /****填充设置参数***
     *参数@int direction 0-正向 1-反向
    ****/
    void fillSetParam(int updown,int speed,int resistance,int direction);
    //设置脉搏血氧
    void setPulseOxygen(const ST_PulseOxygen&);
    //设置中部参数
    void setCenterParam(int left,int right,int length);

    /***********通信相关************/
    /*****设置速度***
     * 参数@int speed 速度大小
     *    @qint8 type 上下肢类型 0-上肢  1-下肢
     * ******/
    void setTrainSpeed(int speed,qint8 type);

    /******设置阻力****
     * 参数@int force 阻力大小
     *    @qint8 type  上下肢类型 0-上肢  1-下肢
     * ********/
    void setTrainFore(int force,qint8 type);

    /******设置方向****
     * 参数@qint8 direction 方向 0-顺时针  1-逆时针
     *    @qint8 type  上下肢类型 0-上肢  1-下肢
     * ********/
    void setTrainDirection(qint8 direction,qint8 type);

    /******设置Fes开关****
     * 参数@qint8 channel 方向 0-电刺激A  1-电刺激B
     *    @bool ok  上下肢类型 false-关  true-开
     * ********/
    void switchFes(qint8 channel,bool ok);
protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_start_Btn_clicked();

    void open_Btn_clicked();

    void close_Btn_clicked();

    void on_upSpeedMinus_Btn_clicked();

    void on_upSpeedPlus_Btn_clicked();

    void on_upForceMinus_Btn_clicked();

    void on_upForcePlus_Btn_clicked();

    void on_upForward_Btn_clicked();

    void on_upBackward_Btn_clicked();

    void on_downSpeedMinus_Btn_clicked();

    void on_downSpeedPlus_Btn_clicked();

    void on_downForceMinus_Btn_clicked();

    void on_downForcePlus_Btn_clicked();

    void on_downForward_Btn_clicked();

    void on_downBackward_Btn_clicked();

    void on_stop_Btn_clicked();

    void on_pause_Btn_clicked();

    void on_switchAFes_Btn_clicked();

    void on_switchBFes_Btn_clicked();

protected:

    virtual void mouseDoubleClickEvent(QMouseEvent *event);
private:
    Ui::GameDisplayPage *ui;
    QPropertyAnimation *m_leftAnimation,*m_rightAnimation;
    bool m_openState;
    QList<QLabel*> m_channelAList,m_channelBList;
    int upDirection;   //上肢旋转方向 0-正 1-逆
    int downDirection; //下肢旋转方向 0-正 1-逆
    SpasmTipsDialog *m_spasmTipsDialog;
};

#endif // GAMEDISPLAYPAGE_H
