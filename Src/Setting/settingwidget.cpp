#include "settingwidget.h"
#include "ui_settingwidget.h"
#include <QDir>
#include <QSettings>
#include <QMessageBox>
#include <QDebug>
#include "ccommunicateapi.h"
SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget),
    m_buttonGroup(nullptr),
    checkTimer(NULL),
    fesAState(false),
    fesBState(false),
    bioelectricityState(false)
{
    ui->setupUi(this);

    //设置按钮互斥,配合样式表
    m_buttonGroup = new QButtonGroup;
    m_buttonGroup->setExclusive(true);
    m_buttonGroup->addButton(ui->systemSetting_Btn);
    m_buttonGroup->addButton(ui->secretManage_Btn);
    m_buttonGroup->addButton(ui->productMsg_Btn);

    ui->originalPasswordTips_Label->setVisible(false);
    ui->confirmPasswordTips_Label->setVisible(false);

    ui->stackedWidget->setCurrentIndex(0);

    checkTimer = new QTimer;
    checkTimer->setInterval(3000);

    connect(checkTimer,SIGNAL(timeout()),this,SLOT(slotCheckTimerSlot()));

    initWidget();
}

SettingWidget::~SettingWidget()
{
    if(m_buttonGroup != nullptr)
        delete m_buttonGroup;
    delete ui;
}

//A侧电刺激盒
void SettingWidget::on_FESA_Btn_clicked()
{
    if(ui->FESA_Btn->text() == tr("启用"))
    {
        ui->FESA_Btn->setText(tr("断开"));
        ui->FESAState_Label->setText(tr("已连接"));
    }
    else if(ui->FESA_Btn->text() == tr("断开"))
    {
        ui->FESA_Btn->setText(tr("启用"));
        ui->FESAState_Label->setText(tr("未连接"));
    }
}


void SettingWidget::on_resetPassword_Btn_clicked()
{
    QString dirPath = "./DependFile/conf/";
    QDir confdir(dirPath);
    if(!confdir.exists())
        confdir.mkdir(dirPath);
    QString confFile(dirPath + "IDconf.ini");
    QSettings iniSetting(confFile, QSettings::IniFormat);
    QString password("111111");
    iniSetting.setValue("password",password);
    iniSetting.setValue("user","xyyl");
    QMessageBox::warning(NULL,tr("提示"),tr("密码重置成功"));
}

//B侧电刺激盒
void SettingWidget::on_FESB_Btn_clicked()
{


    if(ui->FESB_Btn->text() == tr("启用"))
    {
        ui->FESBState_Label->setText(tr("已连接"));
        ui->FESB_Btn->setText(tr("断开"));
    }
    else if(ui->FESB_Btn->text() == tr("断开"))
    {
        ui->FESB_Btn->setText(tr("启用"));
        ui->FESBState_Label->setText(tr("未连接"));
    }
}


void SettingWidget::on_bioelectricity_Btn_clicked()
{
    if(ui->bioelectricity_Btn->text() == tr("启用"))
    {
        ui->bioelectricity_Btn->setText(tr("断开"));
        ui->bioelectricityState_Label->setText(tr("已连接"));
    }
    else if(ui->bioelectricity_Btn->text() == tr("断开"))
    {
        ui->bioelectricity_Btn->setText(tr("启用"));
        ui->bioelectricityState_Label->setText(tr("未连接"));
    }
}


void SettingWidget::on_systemSetting_Btn_clicked()
{
    //系统设置界面
    ui->stackedWidget->setCurrentIndex(0);
}


void SettingWidget::on_secretManage_Btn_clicked()
{
    //密码管理界面
    ui->stackedWidget->setCurrentIndex(1);
    ui->originalPasswordTips_Label->setVisible(false);
    ui->confirmPasswordTips_Label->setVisible(false);
}


void SettingWidget::on_productMsg_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void SettingWidget::on_cancelPassword_Btn_clicked()
{
    ui->originalPassword_LineEdit->clear();
    ui->newPassword_LineEdit->clear();
    ui->confirmPassword_LineEdit->clear();
}


void SettingWidget::on_savePassword_Btn_clicked()
{
    QString originalPassword = ui->originalPassword_LineEdit->text();
    QString dirPath = "./DependFile/conf/";
    QDir confdir(dirPath);
    if(!confdir.exists())
        confdir.mkdir(dirPath);
    QString confFile(dirPath + "IDconf.ini");
    QSettings iniSetting(confFile, QSettings::IniFormat);
    QString password = iniSetting.value("password").toString();
    if(password != originalPassword)
    {
        ui->originalPasswordTips_Label->setText(tr("原密码输入错误"));
        ui->originalPasswordTips_Label->setVisible(true);
        return;
    }

    if(ui->newPassword_LineEdit->text() != ui->confirmPassword_LineEdit->text())
    {
        ui->confirmPasswordTips_Label->setText(tr("两次输入的密码不同"));
        ui->confirmPasswordTips_Label->setVisible(true);
        return;
    }

    iniSetting.setValue("password",ui->confirmPassword_LineEdit->text());

    ui->confirmPasswordTips_Label->setVisible(false);
    ui->originalPasswordTips_Label->setVisible(false);
    ui->confirmPassword_LineEdit->clear();
    ui->newPassword_LineEdit->clear();
    ui->originalPassword_LineEdit->clear();

    QMessageBox::warning(NULL,tr("提示"),tr("密码更新成功"));
}


void SettingWidget::on_CH_RadioButton_clicked()
{

}


void SettingWidget::on_EN_RadioButton_clicked()
{

}

void SettingWidget::slotCheckTimerSlot()
{
    if(!fesAState)
    {
        ui->FESA_Btn->setEnabled(false);
        ui->FESA_Btn->setStyleSheet("background: #E1E1E1;border-radius: 8px;color:white;");
        ui->FESAState_Label->setText(tr("未连接"));
    }
    else
    {
        ui->FESA_Btn->setEnabled(true);
        ui->FESA_Btn->setStyleSheet("background: #0D9DDB;border-radius: 8px;color:white;");
    }

    if(!fesBState)
    {
        ui->FESB_Btn->setEnabled(false);
        ui->FESB_Btn->setStyleSheet("background: #E1E1E1;border-radius: 8px;color:white;");
        ui->FESBState_Label->setText(tr("未连接"));
    }
    else
    {
        ui->FESB_Btn->setEnabled(true);
        ui->FESB_Btn->setStyleSheet("background: #0D9DDB;border-radius: 8px;color:white;");
    }

    if(!bioelectricityState)
    {
        ui->bioelectricity_Btn->setEnabled(false);
        ui->bioelectricity_Btn->setStyleSheet("background: #E1E1E1;border-radius: 8px;color:white;");
        ui->bioelectricityState_Label->setText(tr("未连接"));
    }
    else
    {
        ui->bioelectricity_Btn->setEnabled(true);
        ui->bioelectricity_Btn->setStyleSheet("background: #0D9DDB;border-radius: 8px;color:white;");
    }

}

void SettingWidget::initWidget()
{
    ui->FESA_Btn->setEnabled(false);
    ui->FESB_Btn->setEnabled(false);
    ui->bioelectricity_Btn->setEnabled(false);
}


void SettingWidget::on_reset_Btn_clicked()
{
    CCommunicateAPI::getInstance()->setConfigParam();
}

