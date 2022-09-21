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

private:
    Ui::SpasmTipsDialog *ui;
};

#endif // SPASMTIPSDIALOG_H
