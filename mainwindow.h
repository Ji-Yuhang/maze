#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    MazeView *mazeview_;
};

#endif // MAINWINDOW_H
