#ifndef DATAFORMATE_H
#define DATAFORMATE_H
#include <QWidget>
#define PAGENUM  8          //每页显示数量
#define MAXSHOWNUM  1000    //最大显示数量
#define PERCOUNT 8          //用户每页显示数量
//上位机发送使用
#define PACKHEAD 0xAB       //帧头
#define PACKTAIL 0xCD       //帧尾
//下位机发送使用
#define SLAVEPACKHEAD 0xBA
#define SLAVEPACKTAIL 0xDC
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

//上位机发送指令
typedef enum
{
    BICYCLE_PARAM_CMD = 0x01,          //启动前参数
    REALTIME_PARAM_CMD = 0x02,         //实时调节参数
    SEND_HEARTBEAT_CMD = 0X05          //发送心跳（启用）

}E_SENDCMDID;

//游戏训练状态
typedef enum
{

}E_TRAINSTATE;

//接收下位机指令
typedef enum
{
    BRFORE_START_CMD = 0x00,        //启动前
    AFTER_START_CMD = 0x01,         //启动后
    RECE_HEARTBEAT_CMD = 0x02       //接收心跳(启用)
}E_RECECMDID;

//实时调节参数子指令
typedef enum
{
    RESISTANCE_CMD = 0x01,  //阻力
    PASSIVE_SPEED = 0x02,   //被动转速
    SPASM_LEVEL = 0x03,     //痉挛等级
    SWITCH_DIRECTION = 0x04,//手动换向
    EQUAL_SPEED = 0x08,     //等速转速
    SYNERGY_SPEED = 0x09,   //协同限速
    SPASM_CONFIRM = 0x10    //确认痉挛
}E_REALTIMECMD;

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

/**********与下位机通信--start**********/
//踏车参数
#pragma pack(push)		// 保存原来的字节对齐方式
#pragma pack(1)

//启动前参数
typedef struct
{
    int8_t controlState;//状态控制 0-停止 1启动 2-暂停 3-继续
    int8_t bodyPart;    //训练部位 0-上肢 1-下肢 2-四肢
    int8_t trainMode;   //训练模式 0-被动 1-主动 2-助力 3-等速 4-上下肢协同被动 7-四肢主被动 9-单独主动 10-被动可切主动（主被动）
    int8_t spasmSwitch; //痉挛开关 0-关 1-开
    int8_t spasmLevel;  //痉挛等级1~3挡
    int8_t configPower; //配置功率0~2 低中高
    int8_t switchDirectonTime;//换向时间
    int8_t phaseValue;  //协同相位值
    int8_t direction;   //方向 0-逆向 1-正向
    int8_t speed;       //速度 2~60r/min
    int8_t resistance;  //阻力 Nm  0~20挡
    int8_t spasmType;   //痉挛后方向  1-正向 0-逆向
    uint8_t trainTime; //训练时间 0~120min
}ST_BicycleParam;

//下位机上传参数
typedef struct
{
    int8_t currentMode;         //当前模式
    int8_t direction;           //方向 0-反向 1-正向
    uint8_t downLimpSpeed;      //下肢速度
    uint8_t upLimpSpeed;        //上肢速度
    uint16_t leftHandPosition;  //左手位置
    uint16_t leftFootPosition;  //左脚位置
    uint16_t rightHandPosition; //右手位置
    uint16_t rightFootPosition; //右脚位置
    int8_t upBalance;           //上肢平衡度
    int8_t downBalance;         //下肢平衡度
    uint16_t upLimpCircle;      //上肢圈数
    uint16_t downLimpCircle;    //下肢圈数
    int8_t emergencyState;      //急停 1-触发 0-未触发
    int8_t spasmState;          //痉挛 1-触发 0-未触发
    int8_t error;               //系统故障
    int8_t oxygen;              //血氧数据
    int8_t overSpeedProtect;    //过速保护  0-正常 1-触发
    uint16_t upPower;           //上肢功率
    uint16_t downPower;         //下肢功率
    uint32_t energy;            //能量
}ST_DeviceParam;


#pragma pack(pop)		// 恢复字节对齐方式
/**********与下位机通信--end**********/

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
    int updown; //方向1-正向 0-逆向
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
    QString gamePath;           //游戏路径
    QString iconPath;           //游戏图标路径
    QString gameName;           //游戏可执行文件名
    QString className;          //窗口类名
    QString windownName;        //窗口名
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
