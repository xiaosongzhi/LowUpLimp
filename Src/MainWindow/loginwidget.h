#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QDialog>
class PasswordDialog;
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

    void on_userName_LineEdit_textChanged(const QString &arg1);

    void on_password_LineEdit_textChanged(const QString &arg1);

private:
    Ui::LoginWidget *ui;
    PasswordDialog *passworldDialog;
};

#endif // LOGINWIDGET_H
