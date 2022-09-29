#include "usermanager.h"
#include "ui_usermanager.h"
#include "cdatabaseinterface.h"
#include "dbforrmate.h"
#include <QDebug>
#include <QCheckBox>
#include <QMessageBox>
#include "currentuserdata.h"
#include "selectuserdialog.h"
#include "deleteuserdialog.h"
UserManager::UserManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManager),
    m_userDialog(nullptr),
    m_completer(nullptr),
    m_slectUserDialog(nullptr),
    m_deleteUserDialog(nullptr)
{
    ui->setupUi(this);
    m_userDialog = new UserDialog();
    connect(m_userDialog,&UserDialog::signalUpdateUserTable,this,&UserManager::slotUpdateUserTable);
    initUserTableWidget();
    updateUserTableWidget();
    connect(this,SIGNAL(signalCheckUserChanged(int)),ui->trainRecord_Widget,SLOT(slotCheckUserChanged(int)));

    //设置搜索框自动补全
    m_completer = new QCompleter();
    m_completer->setFilterMode(Qt::MatchStartsWith);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
    m_completer->setMaxVisibleItems(7);
    m_completer->setModel(&stringListModel);
    ui->searchUser_LineEdit->setCompleter(m_completer);
    ui->searchUser_LineEdit->setPlaceholderText(tr("姓名或者ID"));
    connect(ui->searchUser_LineEdit,SIGNAL(editingFinished()),this,SLOT(editComplete()));

    connect(ui->searchUser_LineEdit,&QLineEdit::textChanged,[this](const QString text){
        if(text == "")
        {
            updateUserTableWidget();
        }
    });
//    connect(ui->searchUser_LineEdit,&QLineEdit::textEdited,[this](const QString text){
//        qDebug()<<"textEdited"<<text;
//    });

    m_slectUserDialog = new SelectUserDialog();
    m_deleteUserDialog = new DeleteUserDialog();
}

void UserManager::editComplete()
{
    //此处可用来自动添加被检索时没有的内容,可以将lineEdit中的内容添加到model中，但是在咱们这种情况下不适用
    //目前的需求是将数据库中有的数据显示出来，没有的不需要补全
    qDebug()<<"editComplete";

}

UserManager::~UserManager()
{
    if(m_userDialog)
        delete m_userDialog;
    if(m_completer)
        delete m_completer;
    if(m_slectUserDialog)
        delete m_slectUserDialog;
    if(m_deleteUserDialog)
        delete m_deleteUserDialog;
    delete ui;
}

void UserManager::initUserTableWidget()
{
    ui->user_TableWidget->horizontalHeader()->setVisible(false);
    ui->user_TableWidget->verticalHeader()->setVisible(false);
    ui->user_TableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->user_TableWidget->setAlternatingRowColors(true);
    ui->user_TableWidget->setPalette(QPalette(Qt::lightGray));
    ui->user_TableWidget->setColumnCount(3);
    ui->user_TableWidget->setRowCount(100);
    //    ui->user_TableWidget->setGridStyle(Qt::NoPen);
    ui->user_TableWidget->setShowGrid(false);
    ui->user_TableWidget->setColumnWidth(0,140);
    ui->user_TableWidget->setColumnWidth(1,90);
    ui->user_TableWidget->setColumnWidth(2,240);

    ui->user_TableWidget->setFont(QFont("黑体",15));

    for(int i = 0;i < 100;i++)
    ui->user_TableWidget->setRowHeight(i,68);

    //设置单行选中
    ui->user_TableWidget->setSelectionBehavior(QTableWidget::SelectRows);
    ui->user_TableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置表格所有单元格不可编辑
    ui->user_TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->user_TableWidget,&QTableWidget::cellClicked,[this](int row,int column){
        Q_UNUSED(column)
        //根据行列获取用户ID
        if(row >= m_currentRows)
            return;
        m_currentUserId = ui->user_TableWidget->item(row,2)->data(Qt::DisplayRole).toUInt();
        emit signalCheckUserChanged(m_currentUserId);
    });

    //UI显示问题待解决
    //    ui->user_TableWidget->setFocusPolicy(Qt::NoFocus);
    ui->user_TableWidget->setStyleSheet("QTableWidget::item{outline:none;}"
                                        );
}

void UserManager::updateUserTableWidget()
{
    QString queryStr(QString("select * from PatientTable order by ID DESC"));

    if(CDatabaseInterface::getInstance()->exec(queryStr))
    {
        int tempNum = CDatabaseInterface::getInstance()->getValuesSize();
        int fillTableNum = tempNum < 100 ? tempNum : 100;
        m_currentRows = fillTableNum;
        if(fillTableNum > 0)
        {
            QList<QVariantMap> valueMapList;
            valueMapList = CDatabaseInterface::getInstance()->getValues(0,fillTableNum);
            fillUserTable(valueMapList);
        }
        else
        {
            ui->user_TableWidget->clearContents();
            qDebug()<<"updateUserTableWidget()未查询到符合条件的数据";
        }
    }
    else
        qDebug()<<CDatabaseInterface::getInstance()->getLastError();
}

void UserManager::fillUserTable(const QList<QVariantMap> &ListMap)
{
    ui->user_TableWidget->clearContents();
    wordList.clear();
    for(int row = 0;row < ListMap.size();++row)
    {
        ST_PatientMsg st_PatientMsg = variantMapToPatientMsg(ListMap.at(row));
        //更新自动补全表
        wordList.append(st_PatientMsg.name);
        wordList.append(QString::number(st_PatientMsg.ID));
        stringListModel.setStringList(wordList);
        //第0列
        /***
        QTableWidgetItem *checkItem = new QTableWidgetItem();
        ui->user_TableWidget->setItem(row,0,checkItem);
        QCheckBox *checkBox = new QCheckBox();
        checkBox->setFixedWidth(40);

        checkBox->setLayoutDirection(Qt::RightToLeft);
        //使用该方法时必须先添加QTableWidgetItem
        ui->user_TableWidget->setCellWidget(row,0,checkBox);
        *****/
        //第0列 名字
        QTableWidgetItem *nameItem = new QTableWidgetItem(st_PatientMsg.name);
        //        nameItem->setFlags(nameItem->flags() & (~Qt::ItemIsEditable));  //设置单个单元格不可编辑
        ui->user_TableWidget->setItem(row, 0, nameItem);
        //第1列 性别
        QString sexStr;
        if(0 == st_PatientMsg.sex)
            sexStr = tr("男");
        else if(1 == st_PatientMsg.sex)
            sexStr = tr("女");
        QTableWidgetItem *sexItem = new QTableWidgetItem(sexStr);
        //        nameItem->setFlags(nameItem->flags() & (~Qt::ItemIsEditable));  //设置单个单元格不可编辑
        ui->user_TableWidget->setItem(row, 1, sexItem);

        //第2列 ID
        QTableWidgetItem *IdItem = new QTableWidgetItem(QString::number(st_PatientMsg.ID));
        ui->user_TableWidget->setItem(row, 2, IdItem);

        //        ui->user_TableWidget->cellWidget(row,0)->setGeometry(10,20,10,20);
        ui->user_TableWidget->item(row,0)->setTextAlignment(Qt::AlignCenter);
        ui->user_TableWidget->item(row,1)->setTextAlignment(Qt::AlignCenter);
        ui->user_TableWidget->item(row,2)->setTextAlignment(Qt::AlignCenter);
    }
}

void UserManager::on_searchUser_Btn_clicked()
{
    //首先清理界面
    ui->user_TableWidget->clearContents();
    //检索的情况下不显示添加按钮，只显示符合检索条件的内容
    QString msg = ui->searchUser_LineEdit->text();
    QString query(QString("select * from PatientTable where name = '%1' or id = '%2'").arg(msg).arg(msg));

    QList<QVariantMap> valueMapList;
    if(CDatabaseInterface::getInstance()->exec(query))
    {
        valueMapList = CDatabaseInterface::getInstance()->getValues(0,8);
    }
    if(0 == valueMapList.count())
    {
        qDebug()<<"未找到合适数据";
    }

    fillUserTable(valueMapList);
}

void UserManager::slotUpdateUserTable()
{
    updateUserTableWidget();
}


void UserManager::on_newUser_Btn_clicked()
{
    m_userDialog->setDialogTitle(E_NEW_USER);
}

//选择用户
void UserManager::on_selectUser_Btn_clicked()
{
    QString queryStr(QString("select * from PatientTable where ID = '%1'").arg(m_currentUserId));

    if(CDatabaseInterface::getInstance()->exec(queryStr))
    {
        if(CDatabaseInterface::getInstance()->getValuesSize() > 0)
        {
            QVariantMap userMap = CDatabaseInterface::getInstance()->getValues(0,1).at(0);
            ST_PatientMsg st_patientMsg = variantMapToPatientMsg(userMap);

            m_slectUserDialog->setUserMsg(st_patientMsg);
            m_slectUserDialog->show();
            m_slectUserDialog->exec();
            //设置当前用户
            if(m_slectUserDialog->isSelectUser())
                CurrentUserData::getInstace()->setCurrentUserMsg(st_patientMsg);
        }
        else
            QMessageBox::warning(NULL,tr("提示"),tr("未查到该用户信息"));
    }
}


void UserManager::on_EditUser_Btn_clicked()
{
    m_userDialog->setDialogTitle(E_EDIT_USER,m_currentUserId);
}


void UserManager::on_deleteUser_Btn_clicked()
{
    m_deleteUserDialog->show();
    m_deleteUserDialog->exec();
    if(m_deleteUserDialog->isDeletedUser())
    {
        if(!CDatabaseInterface::getInstance()->deleteRowTable("PatientTable","ID",QString::number(m_currentUserId)))
            qDebug()<<"delete user failed"<<CDatabaseInterface::getInstance()->getLastError();
        updateUserTableWidget();
    }
    else
        return;
    /**********之前的删除方式，可以同时删除多个用户**********
    QList<int> deleteIndexList;
    int deleteUserNum = 0;
    for(int i = 0;i <m_currentRows;++i)
    {
        QCheckBox *checkBox = static_cast<QCheckBox*>(ui->user_TableWidget->cellWidget(i,0));

        if(checkBox->isChecked())
        {
            QString ID = ui->user_TableWidget->item(i,2)->data(Qt::DisplayRole).toString();
            if(!CDatabaseInterface::getInstance()->deleteRowTable("PatientTable","ID",ID))
                qDebug()<<"delete user failed"<<CDatabaseInterface::getInstance()->getLastError();
            else
                ++deleteUserNum;
        }
    }
    if(deleteUserNum > 0)
        QMessageBox::information(NULL,tr("提示"),tr("删除成功"));
    ***************/
}



