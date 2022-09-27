#ifndef SELECTUSERDIALOG_H
#define SELECTUSERDIALOG_H

#include <QDialog>

namespace Ui {
class SelectUserDialog;
}

class SelectUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectUserDialog(QWidget *parent = nullptr);
    ~SelectUserDialog();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_cancel_Btn_clicked();

    void on_confirm_Btn_clicked();

private:
    Ui::SelectUserDialog *ui;
};

#endif // SELECTUSERDIALOG_H
