#ifndef FESSETTING_H
#define FESSETTING_H

#include <QWidget>
class FesTotalParamDialog;
class ChannelDialog;
namespace Ui {
class FesSetting;
}

class FesSetting : public QWidget
{
    Q_OBJECT

public:
    explicit FesSetting(QWidget *parent = nullptr);
    ~FesSetting();

    void initWidget();
    //根据刺激盒的反馈来设置通道状态
    void setChannelState();
private slots:
    void slotTrainTimeBtnClicked();

    void slotFrequentBtnClicked();

    void slotUpTimeBtnClicked();

    void slotDownTimeBtnClicked();

    void slotOpenTimeBtnClicked();

    void slotCloseTimeBtnClicked();

    void slotChannelWidgetClicked(int id);

    void on_FESA_Btn_clicked();

    void on_FESB_Btn_clicked();

    void on_OK_Btn_clicked();

private:
    Ui::FesSetting *ui;
    FesTotalParamDialog *m_FesTotalParamDialog;
    QList<QWidget*> channelList;    //MuscleButton
    ChannelDialog *m_ChannelDialog;
    QList<bool> FESABoxList;
};

#endif // FESSETTING_H
