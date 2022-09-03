#ifndef TRAINRECORD_H
#define TRAINRECORD_H

#include <QWidget>
#include "trainreport.h"
namespace Ui {
class TrainRecord;
}

class TrainRecord : public QWidget
{
    Q_OBJECT

public:
    explicit TrainRecord(QWidget *parent = nullptr);
    ~TrainRecord();

    //根据用户ID来更新表格
    void updateTableByID(int ID);

public slots:
    void slotCheckUserChanged(int);

private slots:
    void on_allSelect_CheckBox_clicked(bool checked);

    void on_delete_Btn_clicked();

    void on_trainRecordFrontPage_btn_clicked();

    void on_trainRecordBackPage_btn_clicked();

    void on_trainRecordGo_btn_clicked();

    void on_createData_Btn_clicked();

    void slotCellWidgetClicked(int row,int cloumn);
private:
    //更新底部控制列表@int num数据条数
    void updateBottomSetting(int num);
    //根据页填充表格 从1开始
    void fillTrainReportTableByPage(int pageIndex);
    /*****
    *说名:填充表格
    *参数@const int index数据读取的下标
    *   @const int showRows读取数据的条数
    ****/
    void fillTrainReportTable(const int index,const int showRows);
    //初始化表格
    void  initTrainRecordTable();
private:
    Ui::TrainRecord *ui;
    TrainReport *m_trainReport;
    QList<QVariantMap> m_valueMapList;
    quint16 m_currentPage;  //当前页 从1开始
    quint16 m_totalPage;    //总页数
    quint16 m_displayNum;   //当前页显示的条数
    int m_userID;
};

#endif // TRAINRECORD_H
