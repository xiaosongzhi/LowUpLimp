#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>
#include "dataformate.h"
#include "loginwidget.h"
//#include "fessetting.h"
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

    void on_login_Btn_clicked();

    void slotCurrentUserChanged();
private:
    void switchPage(E_PAGENAME);
private:
    Ui::CMainWindow *ui;

    LoginWidget *loginDialog;

};

#endif // CMAINWINDOW_H
