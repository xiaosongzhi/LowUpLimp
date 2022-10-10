#ifndef DATAFORMATE_H
#define DATAFORMATE_H
#include <QWidget>
#define PAGENUM  8          //每页显示数量
#define MAXSHOWNUM  1000    //最大显示数量
#define PERCOUNT 8          //用户每页显示数量
#define PACKHEAD 0xFE
typedef enum
{
    E_NEW_USER = 0,
    E_EDIT_USER
}USER_ENUM;

//通信状态
typedef enum
{
    UnconnectedState_E = 0,
    HostLookupState_E,
    ConnectingState_E,
    ConnectedState_E,
    BoundState_E,
    ClosingState_E,
    ListeningState_E

}E_DeviceState;

//页面切换
typedef enum
{
    MainPage_E = 0,             //主界面
    TrainingPage_E,             //训练界面
    UserPage_E,                 //用户界面
    SettingPage_E,              //设置界面
    BicycleParamSet_E,          //踏车参数设置界面
    FesParamSet_E,              //fes设置界面
    FesBicycleParamSet_E,       //FesT踏车设置界面
    BicycleToFes_E              //从踏车界面到FES界面
}E_PAGENAME;

typedef enum
{
    ERROR_EMERGENCY = 0X0000,           //急停报警
    ERROR_CHECKRESULT = 0X0001,         //复位按钮
    ERROR_DEVICEERROR = 0X0002,         //设备报警
    ERROR_SPASMWARNING = 0X0003,        //痉挛报警
    SPASM_ERROR_RESET = 0X0004,         //痉挛复位
    CONTROL_PARAMSET = 0x0100,          //评估模式设定
    MACHINE_ZERO_CHECK= 0x0100,         //机械零点校准
    GYROSCOPE_CHECK = 0X0101,           //陀螺仪校准
    GET_GYROSCOPE_DATA =0X0102,         //获取陀螺仪数据
    GIVE_GYROSCOPE_DATA = 0X0103,       //给出陀螺仪数据
    GET_CIRCLE_ANGLE = 0x0104,          //获取圆周角度
    EVALUATE_CONTROL = 0X1000,          //评估控制
    ARRIVE_EVALUATE_POSITION = 0X1001,  //到达指定评估位置
    SWITCH_PASSIVE_TRAINNING = 0X2000,  //被动训练开启、关闭
    ARRIVED_PASSIVE_POSITION = 0X2001,  //下位机到达被动训练位置
    SET_PASSIVE_PARAMETER = 0X2002,     //设置被动训练参数
    PASSIVE_DEST_POSITION=0X2003,       //被动训练目标数据
    SWITCH_ACTIVE_TRAINNING = 0X3000,   //主动训练开启、关闭
    SET_ACTIVE_TRAINNING_TYPE = 0X3001, //设置主动训练类型值
    SET_ACTIVE_PARAMETER = 0X3002,      //设置主动训练参数
    ARRIVED_ACTIVE_POSITION = 0x3003,   //到达主动训练位置
    DEBUG_CMD = 0x3004,                 //调试指令（被动退出）
    HEART_BEAT_CMD = 0XF000,             //心跳
    QUIT_CMD = 0XF001                    //退出各种状态
}E_CMDID;

//串口配置
typedef struct ST_SerialPortConfig
{
    QString portName;   //端口名
    int32_t baud;       //波特率
    int8_t dataBits;    //数据位
    int8_t parity;      //奇偶校验
    int8_t stopBit;     //停止位
    int8_t flowControl; //流控
    ST_SerialPortConfig()
    {
        portName = "";
        baud = 0;
        dataBits = 0;
        parity = 0;
        stopBit = 0;
        flowControl = 0;
    }

}ST_SerialPortConfig;

//数据库配置
typedef struct ST_DataBaseConfig
{
    QString IP;
    int16_t port;
    QString userName;   //用户名
    QString password;   //密码
    ST_DataBaseConfig()
    {
        IP = "";
        port = 0;
        userName = "";
        password = "";
    }

}ST_DataBaseConfig;


//FES参数中按钮显示
typedef struct
{
    QString muscleName; //肌肉名
    int muscleId;       //肌肉下标(根据下标可判断左右)
    bool connectState;  //连接状态
    int frequency;      //频率
    int plus;           //脉宽
    int minCurrent;     //最小电流
    int maxCurrent;     //最小电流
}ST_MuscleParam;

//高级设置参数
typedef struct
{
    //预热阶段
    int preheatContinueTime;    //预热期持续时间  0~60min step-1
    int preheatAContinueTime;   //加速持续时间   0~60min step-1
    int preheatCompensate;      //转速补偿 -30~30 step-1
    bool isFesOn;               //是否开启电刺激
    int preheatMaxPower;        //预热期最大电量 0~50% step-1%
    int transitionalFesRise;    //电刺激上升幅度 1~100% step-1%
    //积极阶段
    int positiveFChiXuTime;      //向前（持续时间）0~120min step-1
    int positiveFControlSpeed;   //向前(控制速度) 5~60r/min step-1
    int positiveBChiXuTime;      //(向后)持续时间 0~120min step-1
    int positiveBSpeedCompensate;//(向后)转速补偿 -30~30r/min step-1
    int positiveBresistance;     //(向后)阻力扭矩补偿 -20~20Nm step-1
    int timeLimit;               //时间阈值 0~240s step-1s
    int speedLimit;              //转速阈值  -1~-50r/min step-1
    //消极阶段
    bool isSkipPassive;          //跳过此阶段
    int negativeSpeedCompensate; //(向前)转速补偿 -30~30r/min step-1
    int tiredContinueTime;       //持续时间(疲劳侦测) 0~30min
    int tiredSpeedCompensate;    //转速补偿(疲劳侦测) -30~0 step-1
}ST_AdvancedParam;

//脉搏血氧
typedef struct
{
    int pulse;//脉搏
    int oxygen;//血氧
}ST_PulseOxygen;

//游戏界面显示参数
typedef struct
{
    int type;   //0-上肢 1-下肢
    int updown; //方向0-正向 1-逆向
    int power;  //阻力
    int speed;  //速度
}ST_SetBicycleParam;

//游戏相关参数
//更改游戏配置文件的参数(通信文件)
typedef  struct ST_GameParam
{
    int hardLevel;          //难度等级 1-3(此处的难度等级对应范围大小)
    int gameTime;           //游戏运行时间 单位/s
    int speed;              //运行速度 1-5
    int trainingMode;       //训练类型
    QString trainTrackFilePath;  //路径文件
    bool readPosTable;      //是否去读轨迹
    int angleValue;         //分段运动角度
    int trainType;          //被动训练类型1-圆周 2-分段
    int waitTime;           //等待时间
    int maxCircle;          //最大圈数
    ST_GameParam()
    {
        hardLevel = 1;
        gameTime = 0;
        speed = 3;
        trainingMode = 0;
        trainTrackFilePath = "";
        readPosTable = false;
    }
}ST_GameParam;

//该结构体用于读取游戏列表
typedef struct
{
    int gameID;                 //游戏ID
    QString gameName;           //游戏名称
    QString gamePath;           //游戏路径
    QString iconPath;           //游戏图标路径
    QStringList suitTypeList;   //适合的游戏类型  0-被动圆周 1-被动分段 2-主动
}ST_GameMsg;

//游戏控制参数
typedef struct
{
    int MsgId;       //消息ID
    int ID;          //用户ID
    QString userName;//用户名
    int speed;       //速度
    int forceLeft;   //左平衡
    int forceRight;  //右平衡
}ST_GameControlParam;

extern void  Pressure_CheckCRC(uint8_t*buf,int len,uint8_t* CRC_H,uint8_t* CRC_L);
extern void Sleep(int msec);

#endif // DATAFORMATE_H
