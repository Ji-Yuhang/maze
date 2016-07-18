#include "mainwindow.h"
#include <QApplication>
#include "server.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server;
    MainWindow w;
    w.show();

    return a.exec();
}
