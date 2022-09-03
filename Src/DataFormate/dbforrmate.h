#ifndef DBFORRMATE_H
#define DBFORRMATE_H

#include <QDateTime>
#include <QVariantMap>
//用户信息
typedef struct
{
    uint32_t ID;                    //自增性ID，由系统分配控制
    QString name;                   //患者姓名 必填
    QString phone;                  //患者电话
    int sex;                        //0-男性 1-女性
    QDate birthday;                 //生日
    int bodyIndex;                  //训练部位选择 0-下肢  1-上肢 2-上下肢
    QString markMsg;                //备注信息
    int age;                        //患者年龄
}ST_PatientMsg;

//训练记录
typedef struct
{
    QString UUID;
    int ID;                         //用户ID
    QDateTime startTime;            //开始训练时间-用于排序
    QString startTimeStr;           //训练时间字符串版-用于显示
    int trainTime;                  //训练时长 （min）
    int score;                      //游戏得分
    QString bodyPart;               //训练部位
}ST_TrainRecord;


//训练报告
typedef struct
{
    QString UUID;
    int ID;                 //系统ID
    QString name;           //患者姓名
    int sex;                //0-male 1-female
    QString phone;          //手机
    int age;                //年龄
    int trainMode;          //训练模式
    int bodyIndex;          //训练部位
    QString markMsg;        //备注
    int trainTime;          //本次训练时长(分钟)
    int leftBalance;        //左平衡
    int rightBalance;       //右平衡
    float activeLength;     //主动长度
    float passiveLength;    //被动长度
    int activeTime;         //主动时间
    int passiveTime;        //被动时间
    int spasmTimes;         //痉挛次数
    float maxResistance;    //最大阻力
    float averangeResistance;//平均阻力
    float minResistance;     //最小阻力
    QString startTimeStr;    //训练时长字符串版-查看检索

}ST_TrainReport;

extern ST_PatientMsg variantMapToPatientMsg(QVariantMap vMap);
extern ST_TrainReport variantMapToTrainReport(QVariantMap vMap);
extern ST_TrainRecord variantMapToTrainRecord(QVariantMap vMap);

extern QVariantMap patientMsgToVariantMap(const ST_PatientMsg&);
extern QVariantMap trainReportToVariantMap(const ST_TrainReport&);
extern QVariantMap trainRecordToVariantMap(const ST_TrainRecord&);
#endif // DBFORRMATE_H
