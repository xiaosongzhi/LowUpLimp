#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>
#include "dataformate.h"

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

private:
    void switchPage(E_PAGENAME);
private:
    Ui::CMainWindow *ui;


};

#endif // CMAINWINDOW_H
