#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>
#include "dataformate.h"
#include "loginwidget.h"
//#include "fessetting.h"
#include "channeldialog.h"
#include "advanceddialog.h"
#include "deleteuserdialog.h"
#include "emergencystopdialog.h"
#include "festipsdialog.h"
#include "festotalparamdialog.h"
#include "selectuserdialog.h"
#include "spasmtipsdialog.h"
#include "userdialog.h"
#include "gamedisplaypage.h"
namespace Ui {
class CMainWindow;
}

class CMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();
public slots:
    void slotSwitchPage(E_PAGENAME);
private slots:
    void on_test_Btn_clicked();

    void on_advanced_Btn_clicked();

    void on_trainPage_Btn_clicked();

    void on_jipian_Btn_clicked();

    void on_spasm_Btn_clicked();

    void on_emergency_Btn_clicked();

    void on_channel_Btn_clicked();

    void on_allParam_Btn_clicked();

    void on_login_Btn_clicked();

    void on_select_clicked();

    void on_delete_2_clicked();

    void on_new_2_clicked();

private:
    void switchPage(E_PAGENAME);
private:
    Ui::CMainWindow *ui;
    AdvancedDialog *advancedDialog;
    ChannelDialog *channelDialog;
    DeleteUserDialog *deleteUserDialog;
    EmergencyStopDialog *emergencyDialog;
    FesTipsDialog *fesTipsDialog;
    FesTotalParamDialog *fesTotalParamDialog;
    SelectUserDialog *selectUserDialog;
    SpasmTipsDialog *spasmTipsDialog;
    UserDialog *userDialog;
    GameDisplayPage *gameDiplayPage;
    LoginWidget *loginDialog;

};

#endif // CMAINWINDOW_H
