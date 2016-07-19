#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QUdpSocket>
#include <QNetworkInterface>
#include "mainwindow.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_search_clicked();

    void on_create_clicked();

    void onRead();
    void onJoin();

private:
    Ui::Login *ui;
    QUdpSocket socket_;
    QHostAddress getIP();
    QMap<quint32, QHostAddress> knownHosts_;
    QHostAddress serverIp_;
    MainWindow*  main_;

};

#endif // LOGIN_H
