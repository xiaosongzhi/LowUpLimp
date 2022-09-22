#ifndef GAMEDISPLAYPAGE_H
#define GAMEDISPLAYPAGE_H

#include <QWidget>
class QPropertyAnimation;
namespace Ui {
class GameDisplayPage;
}

class GameDisplayPage : public QWidget
{
    Q_OBJECT

public:
    explicit GameDisplayPage(QWidget *parent = nullptr);
    ~GameDisplayPage();

private slots:
    void on_start_Btn_clicked();

    void open_Btn_clicked();

    void close_Btn_clicked();
protected:

    virtual void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::GameDisplayPage *ui;
    QPropertyAnimation *m_leftAnimation,*m_rightAnimation;
    bool m_openState;
};

#endif // GAMEDISPLAYPAGE_H
