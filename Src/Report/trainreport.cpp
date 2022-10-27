#include "trainreport.h"
#include "ui_trainreport.h"
#include "cdatabaseinterface.h"
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QFileDialog>
#include <QMessageBox>
TrainReport::TrainReport(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::TrainReport)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置无边框
    setAttribute(Qt::WA_TranslucentBackground,true);    //设置透明
}

TrainReport::~TrainReport()
{
    delete ui;
}

void TrainReport::setReportData(const ST_TrainReport& st_trainReport,int type)
{
    ui->save_Btn->setVisible(type);
    ui->noSave_Btn->setVisible(type);

    m_st_trainReport = st_trainReport;
    ui->name_Label->setText(st_trainReport.name);
    QString sex = st_trainReport.sex == 1 ? tr("女") :tr("男");
    ui->sex_Label->setText(sex);
    ui->phone_Label->setText(st_trainReport.phone);
    ui->age_Label->setText(QString::number(st_trainReport.age) + tr("岁"));

    ui->trainMode_Label->setText(getTrainMode(st_trainReport.trainMode));

    QString bodyStr;
    switch(st_trainReport.bodyIndex)
    {
    case 0:
        bodyStr = tr("上肢");
        break;
    case 1:
        bodyStr = tr("下肢");
        break;
    case 2:
        bodyStr = tr("四肢");
        break;
    }

    ui->trainPart_Label->setText(bodyStr);

    ui->reportDate_Label->setText(st_trainReport.startTimeStr);

    ui->msg_Label->setText(st_trainReport.markMsg);

    //实际训练时间
    int trainTime = st_trainReport.passiveTime + st_trainReport.activeTime;
    ui->trainTime_Label->setText(QString::number(trainTime) + "s");
    ui->trainLength_Label->setText(QString::number(
                                       st_trainReport.upLimpLength + st_trainReport.downLimpLength) + "m");
    ui->leftBalance_Label->setText(QString::number(st_trainReport.leftBalance) + "%");
    ui->rightBalance_Label->setText(QString::number(st_trainReport.rightBalance) + "%");
    ui->upLimpLength_Label->setText(QString::number(st_trainReport.upLimpLength) + "m");
    ui->downLimpLength_Label->setText(QString::number(st_trainReport.downLimpLength) + "m");
    ui->passiveTime_Label->setText(QString::number(st_trainReport.passiveTime) + "s");
    ui->activeTime_Label->setText(QString::number(st_trainReport.activeTime)+"s");
    ui->spasmTimes_Label->setText(QString::number(st_trainReport.spasmTimes));
    ui->avgResistance_Label->setText(QString::number(st_trainReport.averangeResistance) + "N");
    ui->maxResistance_Label->setText(QString::number(st_trainReport.maxResistance) + "N");
    ui->minResistance_Label->setText(QString::number(st_trainReport.minResistance) + "N");

//    this->show();
    this->exec();

}

QString TrainReport::getTrainMode(int8_t mode)
{

    QString modeName;
    switch(mode)
    {
    case 0:
        modeName = tr("被动训练");
        break;
    case 1:
        modeName = tr("主动训练");
        break;
    case 2:
        modeName = tr("助力训练");
        break;
    case 3:
        modeName = tr("等速训练");
        break;
    case 4:
        modeName = tr("协同被动训练");
        break;
    case 5:
        modeName = tr("上肢带下肢训练");
        break;
    case 6:
        modeName = tr("下肢带上肢训练");
        break;
    case 7:
        modeName = tr("自由训练");
        break;
    case 8:
        modeName = tr("FES训练");
        break;
    }

    return modeName;

}

ST_TrainReport TrainReport::getReportDataByStartTime(QString startTimeStr)
{
    QString queryStr(QString("select * from TrainReportTable where startTimeStr = '%1'").arg(startTimeStr));
    if(CDatabaseInterface::getInstance()->exec(queryStr))
    {
        if(CDatabaseInterface::getInstance()->getValuesSize() > 0)
        {
            m_st_trainReport = variantMapToTrainReport(CDatabaseInterface::getInstance()->getValues(0,1).at(0));
        }
        else
            qDebug()<<"TrainReport::getReportDataByStartTime:未查到符合要求数据";
    }
    else
        qDebug()<<"TrainReport::getReportDataByStartTime"<<CDatabaseInterface::getInstance()->getLastError();

    return m_st_trainReport;
}

bool TrainReport::deleteReportByStartTime(QString startTimeStr)
{
    QString table("TrainReportTable");
    return CDatabaseInterface::getInstance()->deleteRowTable(table,"startTimeStr",startTimeStr);
}

void TrainReport::pixmapImportPDF(const QPixmap &pixmap, QString fileName)
{
    QString filePath;

    filePath = QFileDialog::getSaveFileName(NULL,"保存文件",fileName,tr("*.pdf"));

    QFile pdfFile(filePath);
    if(!pdfFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(NULL,tr("导出文件"),tr("文件打开失败"));
        return;
    }
    QPdfWriter *pdfWriter = new QPdfWriter(&pdfFile);
    QPainter *pic_painter = new QPainter(pdfWriter);
    pdfWriter->setPageSize(QPagedPaintDevice::A4);
    pdfWriter->setResolution(QPrinter::ScreenResolution);

    QRect rect = pic_painter->viewport();
    int factor = rect.width()/pixmap.width();
    pic_painter->scale(factor,factor);
    pic_painter->drawPixmap(10,10,pixmap);

    delete pic_painter;
    delete pdfWriter;

    pdfFile.close();

    QMessageBox::information(NULL,tr("提示"),tr("报告导出成功"));
}

void TrainReport::on_close_Btn_clicked()
{
    this->close();
}


void TrainReport::on_noSave_Btn_clicked()
{
    this->close();
}

void TrainReport::on_save_Btn_clicked()
{
    //将数据存储到数据库中
    QString tableName("TrainReportTable");
    if(!CDatabaseInterface::getInstance()->insertRowTable(tableName,trainReportToVariantMap(m_st_trainReport)))
        qDebug()<<"训练报告存储失败"<<CDatabaseInterface::getInstance()->getLastError();
    else
    {
        QMessageBox::warning(NULL,tr("保存"),tr("报告保存成功"));
        this->close();
    }

}

//导出报告
void TrainReport::on_import_Btn_clicked()
{
    QDateTime dateTime = QDateTime::fromString(m_st_trainReport.startTimeStr,"yyyy-MM-dd hh:mm:ss");
    QString fileName;
    fileName.append(m_st_trainReport.name +"-"+ QString::number(m_st_trainReport.ID));
    fileName.append("-");
    fileName.append(dateTime.toString("yyyyMMddhhmmss"));
    pixmapImportPDF(ui->groupBox->grab(),fileName);
}

void TrainReport::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.fillRect(rect(),QColor(0,0,0,100));
}
