#ifndef GAMECONTAINER_H
#define GAMECONTAINER_H

#include <QWidget>
#include <QProcess>
#include <QWindow>
namespace Ui {
class GameContainer;
}

class GameContainer : public QWidget
{
    Q_OBJECT

public:
    explicit GameContainer(QWidget *parent = nullptr);
    ~GameContainer();

    void startGame(QString path);
private:
    void initProcess();
private:
    Ui::GameContainer *ui;
    QProcess *process;
    int m_exitCode;
    QProcess::ExitStatus m_exitStatus;
    QWindow *m_window;
};

#endif // GAMECONTAINER_H
