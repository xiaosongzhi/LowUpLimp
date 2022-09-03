#include "currentuserdata.h"
#include <QDebug>

CurrentUserData* CurrentUserData::m_currentUserData = NULL;

CurrentUserData::CurrentUserData(QObject *parent)
    : QObject(parent)
{

}

CurrentUserData* CurrentUserData::getInstace()
{
    if(!m_currentUserData)
    {
        m_currentUserData = new CurrentUserData();
    }
    return m_currentUserData;
}

//获取患者信息
ST_PatientMsg CurrentUserData::getCurrentPatientMsg()
{
    return st_CurrentUserData;
}

void CurrentUserData::updateTrainUser()
{
    emit signalUserChanged();
}

void CurrentUserData::setCurrentUserMsg(ST_PatientMsg st_patientMsg)
{
    st_CurrentUserData = st_patientMsg;
    updateTrainUser();
}




