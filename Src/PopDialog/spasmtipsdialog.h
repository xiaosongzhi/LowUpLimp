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
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_confirm_Btn_clicked();

private:
    Ui::SpasmTipsDialog *ui;
};

#endif // SPASMTIPSDIALOG_H
