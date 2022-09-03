#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QDialog>
namespace Ui {
class LoginWidget;
}

class LoginWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWidget(QDialog *parent = nullptr);
    ~LoginWidget();
signals:
    void signalResult(int);
private slots:
    void on_forgetPassword_Btn_clicked();

    void on_confirm_Btn_clicked();

private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H
