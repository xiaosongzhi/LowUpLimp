#include "ccommunicateapi.h"
#include "readconfig.h"
#include "ccommunicationinterface.h"
#include "cserialportinterface.h"
#include "cudpinterface.h"
#include "ctcpsocketinterface.h"
#include <QDebug>

CCommunicateAPI *CCommunicateAPI::m_API = NULL;

CCommunicateAPI::CCommunicateAPI(QObject *parent) :
    QObject(parent),
    m_interface(NULL)
{
    init();
}
CCommunicateAPI::~CCommunicateAPI()
{
    if(m_interface)
    {
        delete m_interface;
        m_interface = NULL;
    }
}

CCommunicateAPI *CCommunicateAPI::getInstance()
{
    if(!m_API)
    {
        m_API = new CCommunicateAPI();
    }
    return m_API;
}

void CCommunicateAPI::init()
{
    commuType = ReadConfig::getInstance()->getCommunicateType();
    //根据通信方式生成不同的对象
    if(0 == commuType) //串口
    {
        m_interface = new CSerialportInterface();
    }
    else if(1 == commuType) //udp
    {
        m_interface = new CUdpInterface();
    }
    else if(2 == commuType) //tcp
    {
        m_interface = new CTcpSocketInterface();
    }
    else if(3 == commuType) //can
    {
        //待添加
    }
    if(m_interface)
    {
        connect(m_interface,SIGNAL(signalReadyRead(QByteArray)),this,SIGNAL(signalReadyRead(QByteArray)));
    }
}

void CCommunicateAPI::sendData(QByteArray sendArray)
{
    char length = sendArray.size();
    sendArray.prepend(length);
    sendArray.prepend(PACKHEAD);
    //添加校验
    char sum = 0;
    sendArray.append(sum);
    sendArray.append(PACKTAIL);
    qDebug()<<sendArray.toHex();
    m_interface->sendDataInterface(sendArray);
}

void CCommunicateAPI::sendData(uint16_t cmdID,QByteArray arrayData)
{
    QByteArray fixedArray;
    fixedArray.resize(5);
    fixedArray[0] = arrayData.length();

    memcpy(fixedArray.data()+3,&cmdID,sizeof(uint8_t));

    fixedArray.append(arrayData);
    sendData(fixedArray);
}
//故障复位
void CCommunicateAPI::resetFault()
{
    QByteArray sendArray;
    sendArray.resize(4);
    sendArray[0] = 0;
    sendArray[1] = 0;
    sendArray[2] = 1;
    sendArray[3] = 0x06;
    sendData(sendArray);
}

//发送心跳
void CCommunicateAPI::sendHeartBeat()
{    
    QByteArray array(4,0);
                      //长度
    array[0] = SEND_HEARTBEAT_CMD;  //指令
    sendData(array);
}

void CCommunicateAPI::sendBicycleParam(const ST_BicycleParam &st_bicycleParam)
{
    QByteArray array(13,0);
    array[0] = BICYCLE_PARAM_CMD;
    memcpy(array.data() + 1,&st_bicycleParam,sizeof(ST_BicycleParam));
    sendData(array);
}

void CCommunicateAPI::sendRealTimeParam(E_REALTIMECMD sbuCmd,quint8 value)
{
    QByteArray array(4,0);
    array[0] = REALTIME_PARAM_CMD;
    array[1] = sbuCmd;
    array[2] = value;
    sendData(array);
}


void CCommunicateAPI::SetquitCmd()
{
//    uint16_t cmdId = QUIT_CMD;

//    QByteArray array;
//    array.resize(0);
//    CCommunicateAPI::getInstance()->sendData(cmdId,array);
}
