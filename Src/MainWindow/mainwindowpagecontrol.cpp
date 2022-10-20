#include "mainwindowpagecontrol.h"
#include <QDebug>
MainWindowPageControl* MainWindowPageControl::m_pageControlInterface = NULL;
MainWindowPageControl::MainWindowPageControl(QObject *parent) : QObject(parent)
{
    ST_runningFlag.evaluateFlag = false;
    ST_runningFlag.gameFlag = false;
    ST_runningFlag.moveRangeFlag = false;
    ST_runningFlag.trainModeFlag = false;
    ST_runningFlag.trainRecordFlag = false;
}

MainWindowPageControl* MainWindowPageControl::getInstance()
{
    if(m_pageControlInterface == NULL)
    {
        m_pageControlInterface = new MainWindowPageControl();
    }
    return m_pageControlInterface;
}

void MainWindowPageControl::setCurrentPage(int pageIndex)
{
    m_currentPageIndex = pageIndex;
    emit signalSwitchPage((E_PAGENAME)pageIndex);
}

void MainWindowPageControl::setMainWindowBtnsLock(bool isLock)
{
    emit signalSetBtnsLock(isLock);
}

int MainWindowPageControl::getCurrentPageIndex()
{
    return  m_currentPageIndex;
}

