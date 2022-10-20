#ifndef MAINWINDOWPAGECONTROL_H
#define MAINWINDOWPAGECONTROL_H

/*************该类主要用于管理页面间的切换***************/
#include "dataformate.h"
#include <QObject>
class MainWindowPageControl : public QObject
{
    Q_OBJECT
public:
    static MainWindowPageControl* getInstance();

    /****设置当前页面****
     * @int pageIndex 目标页面
     * *************/
    void setCurrentPage(int pageIndex);

    //各个模块是否解锁
    void setMainWindowBtnsLock(bool);

    //获取当前页面下标
    int getCurrentPageIndex();

signals:
    void signalSwitchPage(E_PAGENAME pageIndex);

    void signalSetBtnsLock(bool);
    //关闭当前运行的练习
    void signalTurnOffRunning(int pageIndex);
private:
    explicit MainWindowPageControl(QObject *parent = nullptr);

    static MainWindowPageControl* m_pageControlInterface;

    int m_currentPageIndex; //当前页面下标

    //各界面状态
    struct
    {
        bool moveRangeFlag;
        bool trainModeFlag;
        bool gameFlag;
        bool evaluateFlag;
        bool trainRecordFlag;
    }ST_runningFlag;

};

#endif // MAINWINDOWPAGECONTROL_H
