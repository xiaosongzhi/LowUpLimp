#ifndef SPASMTIPSDIALOG_H
#define SPASMTIPSDIALOG_H

#include <QDialog>

namespace Ui {
class SpasmTipsDialog;
}

class SpasmTipsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SpasmTipsDialog(QWidget *parent = nullptr);
    ~SpasmTipsDialog();
    /*****痉挛弹窗以及痉挛次数显示****
     * 参数@bool isVisable是否显示该弹窗
     * 参数@int times痉挛次数
     * ******/
    void setSpasmDialogVisible(bool isVisable,int times);

    /****设置痉挛后方向***
     * @int8_t direction方向 0-逆向 1-正向
     * ****/
    void setSpasmCompletedDirection(int8_t direction);
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_confirm_Btn_clicked();

private:
    Ui::SpasmTipsDialog *ui;
    int8_t m_direction; //0-逆向 1-正向
};

#endif // SPASMTIPSDIALOG_H
