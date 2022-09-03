#ifndef CURRENTUSERDATA_H
#define CURRENTUSERDATA_H

#include <QObject>
#include "dbforrmate.h"


class CurrentUserData : public QObject
{
    Q_OBJECT
public:
    static CurrentUserData* getInstace();
    //获取患者信息
    ST_PatientMsg getCurrentPatientMsg();
    void setCurrentUserMsg(ST_PatientMsg);

    //更新训练用户
    void updateTrainUser();
signals:
    //当前用户显示发生变化
    void signalUserChanged();

private:
    explicit CurrentUserData(QObject *parent = nullptr);

    static CurrentUserData* m_currentUserData;
    //当前用户信息
    ST_PatientMsg st_CurrentUserData;

};

#endif // CURRENTUSERDATA_H
