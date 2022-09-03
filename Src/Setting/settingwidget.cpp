#include "settingwidget.h"
#include "ui_settingwidget.h"
#include <QDir>
#include <QSettings>

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget),
    m_buttonGroup(nullptr)
{
    ui->setupUi(this);

    //设置按钮互斥,配合样式表
    m_buttonGroup = new QButtonGroup;
    m_buttonGroup->setExclusive(true);
    m_buttonGroup->addButton(ui->systemSetting_Btn);
    m_buttonGroup->addButton(ui->secretManage_Btn);
    m_buttonGroup->addButton(ui->productMsg_Btn);

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
        ui->FESAState_Label->setText(tr("断开"));
        ui->FESAState_Label->setText(tr("已连接"));
    }
    else if(ui->FESA_Btn->text() == tr("断开"))
    {
        ui->FESA_Btn->setText(tr("启用"));
        ui->FESAState_Label->setText(tr("已断开"));
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
}

//B侧电刺激盒
void SettingWidget::on_FESB_Btn_clicked()
{
    if(ui->FESB_Btn->text() == tr("启用"))
    {
        ui->FESBState_Label->setText(tr("断开"));
        ui->FESBState_Label->setText(tr("已连接"));
    }
    else if(ui->FESB_Btn->text() == tr("断开"))
    {
        ui->FESB_Btn->setText(tr("启用"));
        ui->FESBState_Label->setText(tr("已断开"));
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
        ui->bioelectricityState_Label->setText(tr("已断开"));
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
}


void SettingWidget::on_productMsg_Btn_clicked()
{

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
        return;
    }

    if(ui->newPassword_LineEdit->text() != ui->newPassword_LineEdit->text())
    {
        ui->confirmPasswordTips_Label->setText(tr("两次输入的密码不同"));
        return;
    }

    iniSetting.setValue("password",password);
}

