#include "mainwindow.h"
#include <QApplication>
#include "server.h"
#include "login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "main thread ID: " << a.thread();

    Server server;
    server.move();
    qDebug() << "server thread ID: " << server.thread();

    Login login;
    login.show();


    return a.exec();
}
