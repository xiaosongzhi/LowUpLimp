#ifndef FESTIPSDIALOG_H
#define FESTIPSDIALOG_H

#include <QDialog>

namespace Ui {
class FesTipsDialog;
}

class FesTipsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FesTipsDialog(QWidget *parent = nullptr);
    ~FesTipsDialog();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_confirm_Btn_clicked();

private:
    Ui::FesTipsDialog *ui;
};

#endif // FESTIPSDIALOG_H
