#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>

class MazeView;
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setServerIp(QHostAddress address, qint16 port);

private:
    Ui::MainWindow *ui;
    MazeView *mazeview_;
};

#endif // MAINWINDOW_H
