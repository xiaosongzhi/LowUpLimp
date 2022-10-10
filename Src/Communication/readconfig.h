#ifndef READCONFIG_H
#define READCONFIG_H

#include <QObject>
#include "dataformate.h"
#include <QMutex>
#include <QMap>
//饿汉式单例

class ReadConfig
{
private:
    ReadConfig();

    static QMutex mutex;
    static ReadConfig *m_pInstance;

    typedef struct ST_AllConfigData
    {
        QString udpServerIP;
        int16_t udpServerPort;
        QString udpClientIP;
        int16_t udpClientPort;
        QString udpGameClientIP;
        int16_t udpGameClientPort;
        QString udpGameServerIP;
        int16_t udpGameServerPort;
        QString tcpIP;
        int16_t tcpPort;
        ST_SerialPortConfig serialConfig;
        ST_DataBaseConfig dataBaseConfig;
        int communicateType = -1;
        QString videoPath;              //视频路径
        QMap<int,QString> videoMap;     //视频提示管理QMap<视频序号，视频名称>
        ST_AllConfigData()
        {
            udpServerIP.clear();
            udpServerPort = 0;
            tcpIP.clear();
            tcpPort = 0;
        }

    }ST_AllConfigData;

    ST_AllConfigData st_configData;
public:
    //获取实例
    static ReadConfig* getInstance();
    //上下位机通信地址
    bool getUdpServerAddress(int16_t &port,QString &IP);
    bool getUdpClientAddress(int16_t &port,QString &IP);


    //获取TCP地址信息
    bool getTcpAddress(int16_t &port,QString &IP);
    //获取串口信息
    bool getSerialPortConfig(ST_SerialPortConfig &serialConfig);
    //获取数据库配置
    bool getDataBaseConfig(ST_DataBaseConfig &databaseConfig);
    //获取通信方式
    int getCommunicateType();

    bool readConfigFile();

    //与游戏通信地址
    bool getGameServerAddress(int16_t &port,QString& IP);
    //游戏地址
    bool getGameClientAddress(int16_t &port,QString& IP);
};

#endif // READCONFIG_H
