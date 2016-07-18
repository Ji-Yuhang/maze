#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QUdpSocket>
#include <QNetworkInterface>
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

private:
    Ui::Login *ui;
    QUdpSocket socket_;
    QHostAddress getIP();
};

#endif // LOGIN_H
