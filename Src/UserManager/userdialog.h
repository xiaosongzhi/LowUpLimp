#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QWidget>
#include "dataformate.h"
namespace Ui {
class UserDialog;
}

class UserDialog : public QWidget
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = nullptr);
    ~UserDialog();

    /*******
     * 说明:设置界面的类型
     * 参数:int type  0-新建  1-编辑
     *     int ID = 0   //查看用户的ID
     * *****/
    void setDialogTitle(USER_ENUM type,int ID = 0);
protected:
    void paintEvent(QPaintEvent *event);
signals:
    void signalUpdateUserTable();
private:
    void setEditUserType(int ID);
    void setNewUserType();

    void initWidget();
private slots:
    void on_cancel_Btn_clicked();

    void on_save_Btn_clicked();

private:
    Ui::UserDialog *ui;
    USER_ENUM m_type; //0-新建 1-编辑
};

#endif // USERDIALOG_H
