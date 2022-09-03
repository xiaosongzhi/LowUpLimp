#include "dbforrmate.h"
#include <QUuid>

ST_PatientMsg variantMapToPatientMsg(QVariantMap vMap)
{
    ST_PatientMsg st_PatientMsg;
    if(vMap.contains("ID"))
        st_PatientMsg.ID = vMap.value("ID").toUInt();
    if(vMap.contains("name"))
        st_PatientMsg.name = vMap.value("name").toString();
    if(vMap.contains("phone"))
        st_PatientMsg.phone = vMap.value("phone").toString();
    if(vMap.contains("sex"))
        st_PatientMsg.sex = vMap.value("sex").toUInt();
    if(vMap.contains("birthday"))
        st_PatientMsg.birthday = vMap.value("birthday").toDate();
    if(vMap.contains("bodyIndex"))
        st_PatientMsg.bodyIndex = vMap.value("bodyIndex").toInt();
    if(vMap.contains("markMsg"))
        st_PatientMsg.markMsg = vMap.value("markMsg").toString();
    if(vMap.contains("age"))
        st_PatientMsg.age = vMap.value("age").toUInt();
    return st_PatientMsg;
}

ST_TrainReport variantMapToTrainReport(QVariantMap vMap)
{
    ST_TrainReport st_TrainReport;
    if(vMap.contains("UUID"))
        st_TrainReport.UUID = vMap.value("UUID").toString();
    if(vMap.contains("ID"))
        st_TrainReport.ID = vMap.value("ID").toInt();
    if(vMap.contains("name"))
        st_TrainReport.name = vMap.value("name").toString();
    if(vMap.contains("sex"))
        st_TrainReport.sex = vMap.value("sex").toInt();
    if(vMap.contains("phone"))
        st_TrainReport.phone = vMap.value("phone").toString();
    if(vMap.contains("age"))
        st_TrainReport.age = vMap.value("age").toUInt();
    if(vMap.contains("trainMode"))
        st_TrainReport.trainMode = vMap.value("trainMode").toInt();
    if(vMap.contains("bodyIndex"))
        st_TrainReport.bodyIndex = vMap.value("bodyIndex").toInt();
    if(vMap.contains("markMsg"))
        st_TrainReport.markMsg = vMap.value("markMsg").toString();
    if(vMap.contains("trainTime"))
        st_TrainReport.trainTime = vMap.value("trainTime").toInt();
    if(vMap.contains("leftBalance"))
        st_TrainReport.leftBalance = vMap.value("leftBalance").toInt();
    if(vMap.contains("rightBalance"))
        st_TrainReport.rightBalance = vMap.value("rightBalance").toInt();
    if(vMap.contains("activeLength"))
        st_TrainReport.activeLength = vMap.value("activeLength").toInt();
    if(vMap.contains("passiveLength"))
        st_TrainReport.passiveLength = vMap.value("passiveLength").toInt();
    if(vMap.contains("passiveTime"))
        st_TrainReport.passiveTime = vMap.value("passiveTime").toInt();
    if(vMap.contains("activeTime"))
        st_TrainReport.activeTime = vMap.value("activeTime").toInt();
    if(vMap.contains("spasmTimes"))
        st_TrainReport.spasmTimes = vMap.value("spasmTimes").toInt();
    if(vMap.contains("maxResistance"))
        st_TrainReport.maxResistance = vMap.value("maxResistance").toFloat();
    if(vMap.contains("minResistance"))
        st_TrainReport.minResistance = vMap.value("minResistance").toFloat();
    if(vMap.contains("averangeResistance"))
        st_TrainReport.averangeResistance = vMap.value("averangeResistance").toFloat();
    if(vMap.contains("startTimeStr"))
        st_TrainReport.startTimeStr = vMap.value("startTimeStr").toString();
    return st_TrainReport;
}

ST_TrainRecord variantMapToTrainRecord(QVariantMap vMap)
{
    ST_TrainRecord st_trainRecord;
    if(vMap.contains("ID"))
        st_trainRecord.ID = vMap.value("ID").toUInt();
    if(vMap.contains("startTime"))
        st_trainRecord.startTime = vMap.value("startTime").toDateTime();
    if(vMap.contains("startTimeStr"))
        st_trainRecord.startTimeStr = vMap.value("startTimeStr").toString();
    if(vMap.contains("trainTime"))
        st_trainRecord.trainTime = vMap.value("trainTime").toInt();
    if(vMap.contains("score"))
        st_trainRecord.score = vMap.value("score").toInt();
    if(vMap.contains("bodyPart"))
        st_trainRecord.bodyPart = vMap.value("bodyPart").toString();
    return st_trainRecord;
}


QVariantMap patientMsgToVariantMap(const ST_PatientMsg& st_PatientMsg)
{
    QVariantMap vMap;
    vMap.insert("ID",st_PatientMsg.ID);
    vMap.insert("name",st_PatientMsg.name);
    vMap.insert("phone",st_PatientMsg.phone);
    vMap.insert("birthday",st_PatientMsg.birthday);
    vMap.insert("sex",st_PatientMsg.sex);
    vMap.insert("bodyIndex",st_PatientMsg.bodyIndex);
    vMap.insert("markMsg",st_PatientMsg.markMsg);
    vMap.insert("age",st_PatientMsg.age);
    return vMap;
}
QVariantMap trainReportToVariantMap(const ST_TrainReport& st_TrainReport)
{
    QVariantMap vMap;
    //添加UUID
    QUuid id = QUuid::createUuid();
    QString strId = id.toString(QUuid::Id128);
    vMap.insert("UUID",strId);
    vMap.insert("ID",st_TrainReport.ID);
    vMap.insert("name",st_TrainReport.name);
    vMap.insert("sex",st_TrainReport.sex);
    vMap.insert("phone",st_TrainReport.phone);
    vMap.insert("age",st_TrainReport.age);
    vMap.insert("trainMode",st_TrainReport.trainMode);
    vMap.insert("bodyIndex",st_TrainReport.bodyIndex);
    vMap.insert("markMsg",st_TrainReport.markMsg);
    vMap.insert("trainTime",st_TrainReport.trainTime);
    vMap.insert("leftBalance",st_TrainReport.leftBalance);
    vMap.insert("rightBalance",st_TrainReport.rightBalance);
    vMap.insert("activeLength",st_TrainReport.activeLength);
    vMap.insert("passiveLength",st_TrainReport.passiveLength);
    vMap.insert("activeTime",st_TrainReport.activeTime);
    vMap.insert("passiveTime",(int)st_TrainReport.passiveTime);
    vMap.insert("spasmTimes",st_TrainReport.spasmTimes);
    vMap.insert("maxResistance",st_TrainReport.maxResistance);
    vMap.insert("averangeResistance",st_TrainReport.averangeResistance);
    vMap.insert("minResistance",st_TrainReport.minResistance);
    vMap.insert("startTimeStr",st_TrainReport.startTimeStr);
    return vMap;
}

QVariantMap trainRecordToVariantMap(const ST_TrainRecord& st_trainRecord)
{
    QVariantMap vMap;
    //添加UUID
    QUuid id = QUuid::createUuid();
    QString strId = id.toString(QUuid::Id128);
    vMap.insert("UUID",strId);
    vMap.insert("ID",st_trainRecord.ID);
    vMap.insert("startTime",st_trainRecord.startTime);
    vMap.insert("startTimeStr",st_trainRecord.startTimeStr);
    vMap.insert("trainTime",st_trainRecord.trainTime);
    vMap.insert("score",st_trainRecord.score);
    vMap.insert("bodyPart",st_trainRecord.bodyPart);
    return vMap;
}
