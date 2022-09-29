#ifndef DELETEUSERDIALOG_H
#define DELETEUSERDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteUserDialog;
}

class DeleteUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteUserDialog(QWidget *parent = nullptr);
    ~DeleteUserDialog();

    bool isDeletedUser();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_cancel_Btn_clicked();

    void on_confirm_Btn_clicked();

private:
    Ui::DeleteUserDialog *ui;
    bool m_isdeleted;
};

#endif // DELETEUSERDIALOG_H
