#ifndef CCOMMUNICATEAPI_H
#define CCOMMUNICATEAPI_H

#include <QObject>
#include "dataformate.h"
class CCommunicationInterface;
class CCommunicateAPI : public QObject
{
    Q_OBJECT
public:
    static CCommunicateAPI *getInstance();

    void sendData(QByteArray);

    /************************************
    *说明:发送数据函数【重载函数】
    *参数：
    *@uint8_t seq：包的序号,默认为0，当发送的数据需要拆包时才会使用
    *@uint8_t id ：自身设备ID号
    *@uint8_t cmdID：协议ID号
    *@QByteArray arrayData：有效数据
    *返回值：无
    ***********************************/
    void sendData(uint16_t cmdID,QByteArray arrayData);

    //故障复位
    void resetFault();

    //心跳开关
    void sendHeartBeat();

    /****测试函数****/
    //启动前参数
    void sendBicycleParam(const ST_BicycleParam&);
    //实时调节参数
    void sendRealTimeParam(E_REALTIMECMD,quint8 value);

    //退出当前状态
    void SetquitCmd();
signals:
    //接收到实际数据
    void signalReadyRead(QByteArray);
private:

    explicit CCommunicateAPI(QObject *parent = nullptr);
    ~CCommunicateAPI();
    void init();

private:
    static CCommunicateAPI *m_API;
    int commuType;
    CCommunicationInterface *m_interface;
};

#endif // CCOMMUNICATEAPI_H
