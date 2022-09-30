#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QSettings>
#include <QDir>
#include "passworddialog.h"
#include <QDebug>
LoginWidget::LoginWidget(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::LoginWidget),
    passworldDialog(nullptr)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    //设置为模态对话框
//    setModal(true);
    connect(this,&LoginWidget::signalResult,this,&LoginWidget::done);

    ui->userNameTips_Label->setVisible(false);
    ui->passwordTips_Label->setVisible(false);

    passworldDialog = new PasswordDialog();

    ui->password_LineEdit->setEchoMode(QLineEdit::Password);

//    ui->password_LineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
}

LoginWidget::~LoginWidget()
{
    if(passworldDialog)
        delete passworldDialog;
    delete ui;
}

void LoginWidget::on_forgetPassword_Btn_clicked()
{
    //弹出提示框，告知获取密码的方式
    passworldDialog->show();

}

void LoginWidget::on_confirm_Btn_clicked()
{
    QString dirPath = "./DependFile/conf/";
    QDir confdir(dirPath);
    if(!confdir.exists())
        confdir.mkdir(dirPath);
    QString confFile(dirPath + "IDconf.ini");
    QSettings iniSetting(confFile, QSettings::IniFormat);
    QString password = iniSetting.value("password").toString();
    QString userName = iniSetting.value("userName").toString();

    if(ui->userName_LineEdit->text() != userName)
    {
        ui->userNameTips_Label->setVisible(true);
        ui->userNameTips_Label->setText(tr("用户名输入错误"));
        return;
    }
    if(ui->password_LineEdit->text() != password)
    {
        ui->passwordTips_Label->setVisible(true);
        ui->passwordTips_Label->setText(tr("密码输入错误"));
        return;
    }
    //设置返回值结果
    emit signalResult(1);
//    this->close();
}


void LoginWidget::on_userName_LineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->userNameTips_Label->setVisible(false);
}


void LoginWidget::on_password_LineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    ui->passwordTips_Label->setVisible(false);
}

