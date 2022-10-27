#ifndef QUITGAMEDIALOG_H
#define QUITGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class QuitGameDialog;
}

class QuitGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuitGameDialog(QWidget *parent = nullptr);
    ~QuitGameDialog();

    int getResult();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_cancel_Btn_clicked();

    void on_confirm_Btn_clicked();

private:
    Ui::QuitGameDialog *ui;
    int m_result;
};

#endif // QUITGAMEDIALOG_H
