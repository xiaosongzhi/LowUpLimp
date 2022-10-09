#ifndef ICEMODULE_H
#define ICEMODULE_H

#include <QObject>
#include "dataformate.h"
class IceModule : public QObject
{
    Q_OBJECT
public:
    static IceModule *getInstance();

    /****设置游戏界面(GameDisplayPage)显示参数****/
    void setFesAParam(int *data,int size);
    void setFesBParam(int *data,int size);

    void setBicycleParam(ST_SetBicycleParam);
signals:
    void signalSetFesAParam(int *data,int size);
    void signalSetFesBParam(int *data,int size);
    void signalSetBicycleParam(ST_SetBicycleParam);
private:
    explicit IceModule(QObject *parent = nullptr);
    static IceModule *m_IceModule;
};

#endif // ICEMODULE_H
