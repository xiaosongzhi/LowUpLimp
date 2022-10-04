#include "userdialog.h"
#include "ui_userdialog.h"
#include "dbforrmate.h"
#include <QSettings>
#include "cdatabaseinterface.h"
#include <QMessageBox>
#include <QDebug>
#include <QListView>
#include <QPainter>
UserDialog::UserDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);    //设置透明
    ui->ID_LineEdit->setReadOnly(true);

    //添加此语句是为了使样式生效
    ui->sex_ComboBox->setView(new QListView());
}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog::setDialogTitle(USER_ENUM type,int ID )
{
    m_type = type;
    switch(type)
    {
    case E_NEW_USER:
        setNewUserType();
        break;
    case E_EDIT_USER:
        setEditUserType(ID);
        break;
    }
}

void UserDialog::on_cancel_Btn_clicked()
{
    this->close();
}

void UserDialog::on_save_Btn_clicked()
{
    ST_PatientMsg st_patientMsg;
    st_patientMsg.ID = ui->ID_LineEdit->text().toUInt();
    st_patientMsg.age =QDate::currentDate().year() - ui->dateEdit->date().year();
    st_patientMsg.birthday = ui->dateEdit->date();
    st_patientMsg.bodyIndex = ui->bodyIndex_ComboBox->currentIndex();
    st_patientMsg.markMsg = ui->textEdit->toPlainText();
    st_patientMsg.name = ui->name_LineEdit->text();
    st_patientMsg.phone = ui->phone_LineEdit->text();
    st_patientMsg.sex = ui->sex_ComboBox->currentIndex();

    QString tableName("PatientTable");
    QVariantMap vMap = patientMsgToVariantMap(st_patientMsg);

    //删除所有空格
    if(st_patientMsg.name.remove(QRegExp("\\s")).isEmpty())
    {
        QMessageBox::information(NULL,tr("提示"),tr("用户名不能为空"));
    }

    if(E_NEW_USER == m_type)
    {
        if(!CDatabaseInterface::getInstance()->insertRowTable(tableName,vMap))
        {
            QString str = CDatabaseInterface::getInstance()->getLastError();
            QMessageBox::information(NULL,tr("提示"),str);
            this->close();
        }
        else
        {
            emit signalUpdateUserTable();
            QMessageBox::information(NULL,tr("提示"),tr("添加成功"));
            this->close();
        }
    }
    else if(E_EDIT_USER == m_type)
    {
        if(!CDatabaseInterface::getInstance()->updateRowTable(tableName,"ID",vMap))
        {
            QString str = CDatabaseInterface::getInstance()->getLastError();
            QMessageBox::information(NULL,tr("提示"),str);
            this->close();
        }
        else
        {
            emit signalUpdateUserTable();
            QMessageBox::information(NULL,tr("提示"),tr("更新成功"));
            this->close();
        }
    }

}

void UserDialog::setEditUserType(int ID)
{
    ui->title_Label->setText(tr("编辑用户"));
    //根据ID查找用户
    QString queryStr(QString("select * from PatientTable  where ID = '%1'").arg(ID));
    ST_PatientMsg st_PatientMsg;
    if(CDatabaseInterface::getInstance()->exec(queryStr))
    {
        if(CDatabaseInterface::getInstance()->getValuesSize() > 0)
        {
            QList<QVariantMap> valueMapList;
            valueMapList = CDatabaseInterface::getInstance()->getValues(0,1);
            st_PatientMsg = variantMapToPatientMsg(valueMapList.at(0));

            ui->name_LineEdit->setText(st_PatientMsg.name);
            ui->sex_ComboBox->setCurrentIndex(st_PatientMsg.sex);
            ui->bodyIndex_ComboBox->setCurrentIndex(st_PatientMsg.bodyIndex);
            ui->textEdit->setText(st_PatientMsg.markMsg);
            ui->phone_LineEdit->setText(st_PatientMsg.phone);
            ui->dateEdit->setDate(st_PatientMsg.birthday);
            ui->ID_LineEdit->setText(QString::number(st_PatientMsg.ID));
        }
        else
        {
            qDebug()<<"未查询到符合条件的数据";
        }
    }
    this->show();
}
void UserDialog::setNewUserType()
{
    ui->title_Label->setText(tr("新建用户"));
    ui->name_LineEdit->clear();
    ui->sex_ComboBox->setCurrentIndex(0);
    ui->bodyIndex_ComboBox->setCurrentIndex(0);
    ui->textEdit->clear();
    ui->phone_LineEdit->clear();
    QDate defaultDate(1990,1,1);
    ui->dateEdit->setDate(defaultDate);
    //自动生成ID
    int ID(100000);
    //先查询数据库查找出最大的ID
    QString query(QString("select * from PatientTable  order by ID DESC"));
    CDatabaseInterface *dataBase = CDatabaseInterface::getInstance();
    if(dataBase->exec(query))
    {
        int size = dataBase->getValuesSize();
        if(size > 0)
        {
            QVariantMap varMap =dataBase->getValues(0,1).at(0);
            ST_PatientMsg st_patient = variantMapToPatientMsg(varMap);
            ID = st_patient.ID+1;
        }
    }
    else
        qDebug()<<dataBase->getLastError();
    ui->ID_LineEdit->setText(QString::number(ID));
    this->show();
}

void UserDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
