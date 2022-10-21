#include "icemodule.h"
IceModule *IceModule::m_IceModule = NULL;
IceModule::IceModule(QObject *parent)
    : QObject{parent}
{

}

IceModule *IceModule::getInstance()
{
    if(!m_IceModule)
        m_IceModule = new IceModule();
    return m_IceModule;
}

void IceModule::setFesAParam(int *data,int size)
{
    emit signalSetFesAParam(data,size);
}
void IceModule::setFesBParam(int *data,int size)
{
    emit signalSetFesBParam(data,size);
}

void IceModule::setBicycleParam(ST_BicycleParam st_setBicycleParam)
{
    emit signalSetBicycleParam(st_setBicycleParam);
}
