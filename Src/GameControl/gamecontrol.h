#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QWidget>
#include "dataformate.h"
#include <QDomDocument>
#include <QProcess>
#include <QUdpSocket>
#include "trainreport.h"

class QTimer;
class GameControl : public QWidget
{
    Q_OBJECT
public:
    //更新游戏参数，通过该文件与游戏进行通信，游戏在启动时读取该文件
    void setGamParam(ST_GameParam&);

    //通过配置表获取所有游戏的信息
    QList<ST_GameMsg> getGameMsgs();

    //读取游戏配置文件
    void readGameConfigMsg();

    //根据游戏名获得游戏信息
    ST_GameMsg getGameMsgByName(int ID);

    //获取选中游戏信息
    ST_GameMsg getCurrentGameMsg();

    //获取实例
    static GameControl* getInstance();

    //启动游戏
    void startGame(QString path);
    //关闭游戏
    void stopGame();

    //发送左右平衡以及速度
    void sendGameControlData(const ST_GameControlParam& );

    //设置当前游戏序号
    void setCurrentGame(int ID);
signals:
    //游戏状态标志
//    void signalGameState(E_TRAINMODE,E_GameState);

    void signalSendDestPosition(float angle);
public slots:
    //游戏数据接收
    void slotReceiveGameData();
    //游戏界面关闭时间
    void slotWaitTimer();
private:
    explicit GameControl(QWidget *parent = nullptr);

    void updateXml(ST_GameParam&);

    void initGameSocket();

//    void parseGameMsg(QByteArray jsonArray);

    //生成报告
    void createTrainReport();
    //停止训练
    void sendStopCmd();

private:
    static GameControl* m_GameParamControl;

    QMap<int,ST_GameMsg> m_mapGameName;

    QProcess* m_Process;

    QUdpSocket *m_gameSocket;

    ST_TrainReport st_TrainReport;

    int m_spasmTimes;   //痉挛次数

    bool isTraining;    //训练状态

    int m_quitType;     //退出类型

//    WaitingDialog *m_waitingDialog;

    TrainReport *m_trainReport;

    QTimer *waitTimer;

    float m_activeMaxAngle; //主动训练中最大的角度
    float m_activeMinAngle; //主动训练中最小角度

    QList<ST_GameMsg> m_gameMsgList;

    int currentGameID;
};

#endif // GAMECONTROL_H
