#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mazeview.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mazeview_(new MazeView)
{
    ui->setupUi(this);
    this->setCentralWidget(mazeview_);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mazeview_;
}

void MainWindow::setServerIp(QHostAddress address, qint16 port)
{
    mazeview_->setServerIp(address, port);
}
