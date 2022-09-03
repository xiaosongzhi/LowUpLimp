#include "trainrecord.h"
#include "qdebug.h"
#include "ui_trainrecord.h"
#include "cdatabaseinterface.h"
#include "dataformate.h"
#include "dbforrmate.h"
#include <QDateTime>
#include <QRandomGenerator>
#include <QLabel>
TrainRecord::TrainRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainRecord),
    m_trainReport(NULL),
    m_currentPage(1),
    m_totalPage(1),
    m_userID(100000)
{
    ui->setupUi(this);
    initTrainRecordTable();
    m_trainReport = new TrainReport();
}

TrainRecord::~TrainRecord()
{
    if(m_trainReport != NULL)
    {
        delete m_trainReport;
        m_trainReport = NULL;
    }
    delete ui;

}


void TrainRecord::updateTableByID(int ID)
{
    m_userID = ID;
    //切换用户时切成首页
    m_currentPage = 1;
    QString queryNameStr(QString("select * from PatientTable  where ID = '%1'").arg(ID));
    if(CDatabaseInterface::getInstance()->exec(queryNameStr))
    {
        //填充用户信息
        if(CDatabaseInterface::getInstance()->getValuesSize() > 0)
        {
            ST_PatientMsg st_patientMsg = variantMapToPatientMsg(CDatabaseInterface::getInstance()->getValues(0,1).at(0));
            ui->name_Label->setText(st_patientMsg.name);
            //下面填充性别
        }
    }

    //根据ID查找用户
    QString queryStr(QString("select * from TrainRecordTable  where ID = '%1' order by 'startTime'").arg(ID));
    if(CDatabaseInterface::getInstance()->exec(queryStr))
    {
        //最多显示500条
        int fillTableNum = CDatabaseInterface::getInstance()->getValuesSize();

        if(fillTableNum > 0)
        {
            //更新底部控制显示
            updateBottomSetting(fillTableNum);

            fillTableNum = (fillTableNum < MAXSHOWNUM ? fillTableNum : MAXSHOWNUM);
            m_valueMapList = CDatabaseInterface::getInstance()->getValues(0,fillTableNum);

            //填充首页
            fillTrainReportTableByPage(1);
        }
        else
        {
            qDebug()<<"TrainRecord::updateTableByID未查询到符合要求的数据";
            m_displayNum = 0;
            ui->trainRecord_TableWidget->clearContents();
            m_totalPage = 1;
            QString pageShow = QString("%1/%2").arg(m_currentPage).arg(m_totalPage);
            ui->trainRecordIndexPage_Label->setText(pageShow);
            ui->trainRecordDestPage_LineEdit->setText("1");
        }
    }
    else
        qDebug()<<"TrainRecord::updateTableByID"<<CDatabaseInterface::getInstance()->getLastError();
}

void TrainRecord::fillTrainReportTable(const int index,const int showRows)
{
    //没有合适数据
    if(showRows < 1)
        return;

    for(int row = 0;row < showRows;row++)
    {
        ST_TrainRecord st_trainRecord = variantMapToTrainRecord(m_valueMapList.at(index + row));
        //第0列checkBox
        QTableWidgetItem *checkItem = new QTableWidgetItem();
        ui->trainRecord_TableWidget->setItem(row,0,checkItem);
        QCheckBox *checkBox = new QCheckBox();
        checkBox->setFixedWidth(40);
        checkBox->setLayoutDirection(Qt::RightToLeft);
        ui->trainRecord_TableWidget->setCellWidget(row,0,checkBox);
        //第1列 训练时间
        QTableWidgetItem *timeItem = new QTableWidgetItem(st_trainRecord.startTimeStr);
        ui->trainRecord_TableWidget->setItem(row, 1, timeItem);
        //第2列 训练时长
        QTableWidgetItem *durationItem = new QTableWidgetItem(QString::number(st_trainRecord.trainTime));
        ui->trainRecord_TableWidget->setItem(row, 2, durationItem);
        //第3列 得分
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(st_trainRecord.score));
        ui->trainRecord_TableWidget->setItem(row, 3, scoreItem);
        //第4列 训练部位
        QTableWidgetItem *bodyItem = new QTableWidgetItem(st_trainRecord.bodyPart);
        ui->trainRecord_TableWidget->setItem(row, 4, bodyItem);

        //第5列 查看--设置图片在表格中居中
#if 0
        QTableWidgetItem *importItem = new QTableWidgetItem();
        importItem->setIcon(QIcon(":/DependFile/Source/import.png"));
        ui->trainRecord_TableWidget->setItem(row,5,importItem);
#else
        QLabel *label = new QLabel();
        label->setPixmap(QPixmap(":/DependFile/Source/import.png"));
        label->setAlignment(Qt::AlignCenter);
        ui->trainRecord_TableWidget->setCellWidget(row,5,label);
#endif

#if 0
        //第6列 删除
        QTableWidgetItem *deleteItem = new QTableWidgetItem();
        deleteItem->setIcon(QIcon(":/DependFile/Source/delete.png"));
        ui->trainRecord_TableWidget->setItem(row,6,deleteItem);
#else
        QLabel *deletelabel = new QLabel();
        deletelabel->setPixmap(QPixmap(":/DependFile/Source/delete.png"));
        deletelabel->setAlignment(Qt::AlignCenter);
        ui->trainRecord_TableWidget->setCellWidget(row,6,deletelabel);
#endif
        //设置居中
        for(int i = 1;i < 4;i++)
            ui->trainRecord_TableWidget->item(row,i)->setTextAlignment(Qt::AlignCenter);
    }
}

void TrainRecord::fillTrainReportTableByPage(int pageIndex)
{
    //判断页数下标的合法性
    if(pageIndex > m_totalPage)
        return;
    //不是当前页则清空全选
    ui->allSelect_CheckBox->setChecked(false);
    //清空表格
    ui->trainRecord_TableWidget->clearContents();
    //当前页显示条数
    int displayRow = m_valueMapList.size() - (pageIndex-1)*PAGENUM;
    displayRow = displayRow > PAGENUM ? PAGENUM:displayRow;
    //当页显示的条数
    m_displayNum = displayRow;
    //根据页下标获取要显示的数据条数
    fillTrainReportTable((pageIndex-1)*PAGENUM,displayRow);
}

//初始化表格
void TrainRecord::initTrainRecordTable()
{
    ui->trainRecord_TableWidget->horizontalHeader()->setVisible(false);
    ui->trainRecord_TableWidget->verticalHeader()->setVisible(false);
    //关闭右侧和下方滑条
    ui->trainRecord_TableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->trainRecord_TableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->trainRecord_TableWidget->setAlternatingRowColors(true);
    ui->trainRecord_TableWidget->setShowGrid(false);
    ui->trainRecord_TableWidget->setColumnWidth(0,50);

    ui->trainRecord_TableWidget->setColumnCount(7);

    ui->trainRecord_TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置整行选中
    //    ui->trainRecord_TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置不可选
    ui->trainRecord_TableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    ui->trainRecord_TableWidget->setColumnCount(7);
    ui->trainRecord_TableWidget->setRowCount(8);

    connect(ui->trainRecord_TableWidget,&QTableWidget::cellClicked,this,&TrainRecord::slotCellWidgetClicked);

    //设置table隐藏边框（通过测试以下两种方式都可行），任选其一
    //(1)方法一 设置不获取焦点
//    ui->trainRecord_TableWidget->setFocusPolicy(Qt::NoFocus);
    //(2)方法二 通过样式表设置
    ui->trainRecord_TableWidget->setStyleSheet("QTableWidget{outline:none;}"
                                               "QTableWidget::item{background:white;}");
    //(3)方法三 自定义代理实现
}

void TrainRecord::slotCellWidgetClicked(int row,int cloumn)
{
    if(row >= m_displayNum)
        return;
    //获取主键(时间)
    QString startTimeStr = ui->trainRecord_TableWidget->item(row,1)->data(Qt::DisplayRole).toString();
    switch(cloumn)
    {
    case 5:     //查看报告
    {
        ST_TrainReport st_trainReport = m_trainReport->getReportDataByStartTime(startTimeStr);
        m_trainReport->setReportData(st_trainReport,0);
    }
        break;
    case 6:     //删除记录
    {
        //删除记录条目
        QString table("TrainRecordTable");
        if(!CDatabaseInterface::getInstance()->deleteRowTable(table,"startTimeStr",startTimeStr))
            qDebug()<<CDatabaseInterface::getInstance()->getLastError();
        //删除该记录对应的报告数据
        if(!m_trainReport->deleteReportByStartTime(startTimeStr))
        {
            qDebug()<<"删除报告失败";
        }

        if(1 == m_displayNum)//整页删除
        {
            if(m_currentPage >=2)
                --m_currentPage;
        }

        QString queryStr(QString("select * from TrainRecordTable  where ID = '%1' order by 'startTime'").arg(m_userID));
        int fillTableNum = 0;
        if(CDatabaseInterface::getInstance()->exec(queryStr))
        {
            //最多显示500条
            fillTableNum  = CDatabaseInterface::getInstance()->getValuesSize();

            if(fillTableNum > 0)
            {
                fillTableNum = (fillTableNum < MAXSHOWNUM ? fillTableNum : MAXSHOWNUM);
                m_valueMapList = CDatabaseInterface::getInstance()->getValues(0,fillTableNum);
            }
            else
            {
                //清空表格
                ui->trainRecord_TableWidget->clearContents();
                m_displayNum = 0;
                qDebug()<<"所有数据都已删除";
                return;
            }
        }
        //更新底部控制显示
        updateBottomSetting(fillTableNum);
        //更新显示界面
        fillTrainReportTableByPage(m_currentPage);
    }
        break;
    }
}

void TrainRecord::on_allSelect_CheckBox_clicked(bool checked)
{
    //要选中的条数m_displayNum
    for(int i = 0;i < m_displayNum;++i)
    {
        QCheckBox *checkBox = static_cast<QCheckBox*>(ui->trainRecord_TableWidget->cellWidget(i,0));
        checkBox->setChecked(checked);
    }
}

//删除选中项
void TrainRecord::on_delete_Btn_clicked()
{
    qDebug()<<"m_displayNum"<<m_displayNum;
    //删除条数计数
    int deleteNum = 0;
    for(int i = 0;i <m_displayNum;++i)
    {
        QCheckBox *checkBox = static_cast<QCheckBox*>(ui->trainRecord_TableWidget->cellWidget(i,0));

        if(checkBox->isChecked())
        {
            QString startTimeStr = ui->trainRecord_TableWidget->item(i,1)->data(Qt::DisplayRole).toString();
            if(!CDatabaseInterface::getInstance()->deleteRowTable("TrainRecordTable","startTimeStr",startTimeStr))
                qDebug()<<"delete user failed"<<CDatabaseInterface::getInstance()->getLastError();
            else
                ++deleteNum;
        }
    }

    QString queryStr(QString("select * from TrainRecordTable  where ID = '%1' order by 'startTime'").arg(m_userID));
    int fillTableNum = 0;
    if(CDatabaseInterface::getInstance()->exec(queryStr))
    {
        //最多显示500条
        fillTableNum  = CDatabaseInterface::getInstance()->getValuesSize();

        if(fillTableNum > 0)
        {
            fillTableNum = (fillTableNum < MAXSHOWNUM ? fillTableNum : MAXSHOWNUM);
            m_valueMapList = CDatabaseInterface::getInstance()->getValues(0,fillTableNum);
        }
        else
        {
            //清空表格
            ui->trainRecord_TableWidget->clearContents();
            m_displayNum = 0;
            qDebug()<<"所有数据都已删除";
            return;
        }
    }
    //删除完成之后重新整理表格结构
    if(deleteNum == m_displayNum)//整页删除
    {
        if(m_currentPage >=2)
            --m_currentPage;
    }
    //更新底部控制显示
    updateBottomSetting(fillTableNum);
    //更新显示界面
    fillTrainReportTableByPage(m_currentPage);

    ui->allSelect_CheckBox->setChecked(false);
}

//前一页
void TrainRecord::on_trainRecordFrontPage_btn_clicked()
{
    if(m_currentPage <= 1)
        return;
    fillTrainReportTableByPage(--m_currentPage);
    QString pageShow = QString("%1/%2").arg(m_currentPage).arg(m_totalPage);
    ui->trainRecordIndexPage_Label->setText(pageShow);
}

//后一页
void TrainRecord::on_trainRecordBackPage_btn_clicked()
{
    if(m_currentPage >= m_totalPage)
        return;
    fillTrainReportTableByPage(++m_currentPage);
    QString pageShow = QString("%1/%2").arg(m_currentPage).arg(m_totalPage);
    ui->trainRecordIndexPage_Label->setText(pageShow);
}


void TrainRecord::on_trainRecordGo_btn_clicked()
{
    int destPage = ui->trainRecordDestPage_LineEdit->text().toUInt();
    fillTrainReportTableByPage(destPage);
}

void TrainRecord::updateBottomSetting(int num)
{
    int pageNum = num/PAGENUM;
    if(num%PAGENUM)
        pageNum+=1;
    //设置总页数
    m_totalPage = pageNum;

    QString pageShow = QString("%1/%2").arg(m_currentPage).arg(m_totalPage);
    ui->trainRecordIndexPage_Label->setText(pageShow);
    ui->trainRecordDestPage_LineEdit->setText("1");
}

//生成数据
void TrainRecord::on_createData_Btn_clicked()
{
    int createNum = ui->createNum_LineEdit->text().toInt();
    //为当前每个ID生成五条数据
    QString queryStr(QString("select * from PatientTable order by ID DESC"));

    if(CDatabaseInterface::getInstance()->exec(queryStr))
    {
        int tempNum = CDatabaseInterface::getInstance()->getValuesSize();
        int fillTableNum = tempNum < MAXSHOWNUM ? tempNum : MAXSHOWNUM;
        if(fillTableNum > 0)
        {
            QList<QVariantMap> valueMapList;
            valueMapList = CDatabaseInterface::getInstance()->getValues(0,fillTableNum);
            for(int row = 0;row < valueMapList.size();++row)
            {
                ST_PatientMsg st_PatientMsg = variantMapToPatientMsg(valueMapList.at(row));
                for(int i = 0;i < createNum;++i)
                {
                    //生成记录数据表
                    ST_TrainRecord st_trainRecord;
                    st_trainRecord.ID = st_PatientMsg.ID;
                    quint32 x = QRandomGenerator::global()->generate();

                    st_trainRecord.bodyPart = QString::number(x%4);
                    st_trainRecord.score = x%100;
                    st_trainRecord.trainTime = x%60;
                    st_trainRecord.startTime = QDateTime::currentDateTime().addSecs(x%10000);
                    st_trainRecord.startTimeStr = st_trainRecord.startTime.toString("yyyy-MM-dd hh:mm:ss");

                    if(!CDatabaseInterface::getInstance()->insertRowTable("TrainRecordTable",trainRecordToVariantMap(st_trainRecord)))
                    {
                        qDebug()<<"TrainRecord::on_createData_Btn_clicked"<<CDatabaseInterface::getInstance()->getLastError();
                    }
                    //生成训练报告数据
                    ST_TrainReport st_trainReport;
                    st_trainReport.ID = st_PatientMsg.ID;
                    st_trainReport.name = st_PatientMsg.name;
                    st_trainReport.sex = st_PatientMsg.sex;
                    st_trainReport.phone = st_PatientMsg.phone;
                    st_trainReport.age = st_PatientMsg.age;
                    st_trainReport.trainMode = x%5;
                    st_trainReport.bodyIndex = st_PatientMsg.bodyIndex;
                    st_trainReport.markMsg = st_PatientMsg.markMsg;
                    st_trainReport.trainTime = st_trainRecord.trainTime;
                    st_trainReport.leftBalance = x%100;
                    st_trainReport.rightBalance = x%100;
                    st_trainReport.activeLength = x%1000;
                    st_trainReport.passiveLength = x%1000;
                    st_trainReport.activeTime = x%100;
                    st_trainReport.passiveTime = x%100;
                    st_trainReport.spasmTimes = x%3;
                    st_trainReport.maxResistance = x%50;
                    st_trainReport.minResistance = x%10;
                    st_trainReport.averangeResistance = (st_trainReport.minResistance+st_trainReport.maxResistance)/2.f;
                    st_trainReport.startTimeStr = st_trainRecord.startTimeStr;

                    QString tableName("TrainReportTable");
                    if(!CDatabaseInterface::getInstance()->insertRowTable(tableName,trainReportToVariantMap(st_trainReport)))
                        qDebug()<<"训练报告存储失败"<<CDatabaseInterface::getInstance()->getLastError();
                }
            }
        }
        else
        {
            ui->trainRecord_TableWidget->clearContents();
            qDebug()<<"updateUserTableWidget()未查询到符合条件的数据";
        }
    }
    else
        qDebug()<<CDatabaseInterface::getInstance()->getLastError();
}

void TrainRecord::slotCheckUserChanged(int ID)
{
    //更新显示列表
    updateTableByID(ID);
}
