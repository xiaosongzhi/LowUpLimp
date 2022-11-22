#ifndef TRAINMANAGER_H
#define TRAINMANAGER_H

#include <QWidget>

namespace Ui {
class TrainManager;
}

class TrainManager : public QWidget
{
    Q_OBJECT

public:
    explicit TrainManager(QWidget *parent = nullptr);
    ~TrainManager();

private slots:
    void on_bicycleTrain_Btn_clicked();

    void on_fesBicycleTrain_Btn_clicked();

    void on_fesTrain_Btn_clicked();

    void on_setting_Btn_clicked();

    void on_shutDown_Btn_clicked();

private:
    Ui::TrainManager *ui;
};

#endif // TRAINMANAGER_H
