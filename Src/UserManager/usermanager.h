#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QWidget>
#include "userdialog.h"
#include <QCompleter>
#include <QStringListModel>
class SelectUserDialog;
namespace Ui {
class UserManager;
}

class UserManager : public QWidget
{
    Q_OBJECT
public:
    explicit UserManager(QWidget *parent = nullptr);
    ~UserManager();

private slots:
    void on_newUser_Btn_clicked();

    void on_selectUser_Btn_clicked();

    void on_EditUser_Btn_clicked();

    void on_deleteUser_Btn_clicked();

    void on_searchUser_Btn_clicked();

    void editComplete();

public slots:
    void slotUpdateUserTable();

signals:
   void signalCheckUserChanged(int);

private:
    //初始化用户列表
    void initUserTableWidget();
    //更新用户列表
    void updateUserTableWidget();
    //填充Usertable
    void fillUserTable(const QList<QVariantMap> &);
private:
    Ui::UserManager *ui;
    UserDialog *m_userDialog;
    int m_currentRows;          //当前有效行数
    int m_currentUserId;        //当前用户ID
    QCompleter *m_completer;    //自动补全
    QStringListModel stringListModel;
    QStringList wordList;       //自动补全文字集
    SelectUserDialog *m_slectUserDialog;
};

#endif // USERMANAGER_H
