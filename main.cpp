#include "mainwindow.h"
#include <QApplication>
#include "server.h"
#include "login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Server server;

    Login login;
    login.show();
//    MainWindow w;
//    w.show();

    return a.exec();
}
