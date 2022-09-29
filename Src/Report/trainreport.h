#ifndef TRAINREPORT_H
#define TRAINREPORT_H

#include <QWidget>
#include "dbforrmate.h"
namespace Ui {
class TrainReport;
}

class TrainReport : public QWidget
{
    Q_OBJECT

public:
    explicit TrainReport(QWidget *parent = nullptr);
    ~TrainReport();

    //参数 @int type  1-训练生成报告  0-查看导出报告
    void  setReportData(const ST_TrainReport&,int type);

    ST_TrainReport getReportDataByStartTime(QString startTimeStr);

    bool deleteReportByStartTime(QString startTimeStr);
protected:
    void paintEvent(QPaintEvent *event);
private:
    /***将图片导出到pdf**
     * @const QPixmap &pixmap  要保存的图片
     * @QString fileName       pdf的默认保存的名字
     * *********/
    void pixmapImportPDF(const QPixmap &pixmap,QString fileName);
private slots:
    void on_close_Btn_clicked();

    void on_noSave_Btn_clicked();

    void on_save_Btn_clicked();

    void on_import_Btn_clicked();

private:
    Ui::TrainReport *ui;
    ST_TrainReport m_st_trainReport;
};

#endif // TRAINREPORT_H
