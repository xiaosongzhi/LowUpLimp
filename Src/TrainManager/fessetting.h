#ifndef FESSETTING_H
#define FESSETTING_H

#include <QWidget>

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
private slots:


    void on_groupBox_clicked();

private:
    Ui::FesSetting *ui;
};

#endif // FESSETTING_H
