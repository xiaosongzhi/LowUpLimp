#ifndef GAMEDISPLAYPAGE_H
#define GAMEDISPLAYPAGE_H

#include <QWidget>

namespace Ui {
class GameDisplayPage;
}

class GameDisplayPage : public QWidget
{
    Q_OBJECT

public:
    explicit GameDisplayPage(QWidget *parent = nullptr);
    ~GameDisplayPage();

private:
    Ui::GameDisplayPage *ui;
};

#endif // GAMEDISPLAYPAGE_H
