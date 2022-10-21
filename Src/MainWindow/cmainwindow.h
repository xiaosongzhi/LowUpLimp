#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>
#include "dataformate.h"
#include "loginwidget.h"
//#include "fessetting.h"
#include "gamedisplaypage.h"
#include <QProcess>
#include <QWindow>

class QProcess;
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

    void slot_Timerout();
private slots:

    void on_login_Btn_clicked();

    void slotCurrentUserChanged();
    void on_startGame_Btn_clicked();

private:
    void switchPage(E_PAGENAME);

    void startGame(QString path);
private:
    Ui::CMainWindow *ui;

    LoginWidget *loginDialog;

    QProcess *process;
    int m_exitCode;
    QProcess::ExitStatus m_exitStatus;
    QWindow *m_window;
    GameDisplayPage *m_gameDisplayPage;
    QProcess* m_Process;
};

#endif // CMAINWINDOW_H
