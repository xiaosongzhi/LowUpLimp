#include "cserialportinterface.h"
#include <QApplication>
#include "readconfig.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>

//#pragma execution_character_set("utf-8")

CSerialportInterface::CSerialportInterface():m_serialPort(NULL)
{
    receiveArray.clear();
    if(!m_serialPort)
    {
        m_serialPort = new QSerialPort();
        connect(m_serialPort,&QSerialPort::readyRead,this,&CSerialportInterface::receiveDataInterface);
        connect(m_serialPort,&QSerialPort::errorOccurred,this,&CSerialportInterface::displayError);
        setConfigParam();
    }
}
CSerialportInterface::~CSerialportInterface()
{
    if(m_serialPort)
    {
        delete m_serialPort;
        m_serialPort = NULL;
    }
}
//配置参数
bool CSerialportInterface::setConfigParam()
{
    m_serialPort->close();
    ST_SerialPortConfig st_SerialConfig;
    if(!ReadConfig::getInstance()->getSerialPortConfig(st_SerialConfig))
    {
        QMessageBox::warning(NULL,tr("警告"),tr("获取串口配置失败"),QMessageBox::Retry);
        return false;
    }

    QSerialPortInfo m_SerialPortInfo;
    QStringList serialPortNames;
    foreach(m_SerialPortInfo,QSerialPortInfo::availablePorts())
    {
        QSerialPort serialport;
        serialport.setPort(m_SerialPortInfo);

        if(serialport.open(QIODevice::ReadWrite))
        {
            serialPortNames.append(m_SerialPortInfo.portName());
            serialport.close();
        }
    }
    if(serialPortNames.isEmpty())
    {
        QMessageBox::warning(NULL,tr("警告"),tr("无可用串口"),QMessageBox::Retry);
        return false;
    }

    if(m_serialPort)
    {
        m_serialPort->setPortName(st_SerialConfig.portName);
        m_serialPort->setReadBufferSize(200);
        if(m_serialPort->open(QIODevice::ReadWrite))
        {
            m_serialPort->setBaudRate(st_SerialConfig.baud);
            m_serialPort->setDataBits(QSerialPort::Data8);
            m_serialPort->setParity(QSerialPort::NoParity);
            m_serialPort->setStopBits(QSerialPort::OneStop);
            m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
        }
        else
        {
            QMessageBox::warning(NULL,tr("警告"),tr("串口打开失败"),QMessageBox::Retry);
            return false;
        }
    }

    return true;
}
//发送数据接口
void CSerialportInterface::sendDataInterface(QByteArray sendArray)
{
    if(m_serialPort)
    {
        if(m_serialPort->isOpen())
            m_serialPort->write(sendArray);
        else
            qDebug()<<tr("串口已关闭");
    }
}
//接收数据接口
void CSerialportInterface::receiveDataInterface()
{
    QByteArray buf;
    buf = m_serialPort->readAll();
    receiveArray.append(buf);

    //    qDebug()<<"receiveArray"<<receiveArray.toHex();

    while(!receiveArray.isEmpty())
    {
        if(receiveArray[0] != (char)SLAVEPACKHEAD)
        {
            receiveArray.remove(0,1);
        }
        else
        {
            //获取有效数据长度
            uint8_t datalen = 0;
            memcpy(&datalen,receiveArray.constData()+1,sizeof(uint8_t));

            if(receiveArray.length() >= datalen + 4)
            {
                //校验成功
                if((uint8_t)receiveArray[datalen+3] ==  SLAVEPACKTAIL)
                {
                    emit  signalReadyRead(receiveArray.mid(0,datalen + 4));
                    receiveArray.remove(0,datalen + 4);
                }
                else //校验失败
                {
                    //方式1 丢弃本包
                    receiveArray.remove(0,datalen + 4);
                }
            }
            else    //数据不够，直接退出继续接收
                break;
        }
    }
}

void CSerialportInterface::displayError(QSerialPort::SerialPortError error)
{
    QString lastError("");
    switch(error)
    {
    case QSerialPort::DeviceNotFoundError:
        lastError = "DeviceNotFoundError";
        break;
    case QSerialPort::PermissionError:
        lastError = "PermissionError";
        break;
    case QSerialPort::OpenError:
        lastError = "OpenError";
        break;
    case QSerialPort::NotOpenError:
        lastError = "NotOpenError";
        break;
    case QSerialPort::WriteError:
        lastError = "WriteError";
        break;
    case QSerialPort::ReadError:
        lastError = "ReadError";
        break;
    case QSerialPort::UnknownError:
        lastError = "UnknownError";
        break;
    default:
        break;
    }
    qDebug()<<lastError;
    emit signalDisplayError(lastError);
}

//解析数据
void CSerialportInterface::analysisProtocal(QByteArray)
{

}
