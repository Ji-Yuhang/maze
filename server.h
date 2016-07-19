#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer();
    ~TcpServer();
    void start();

    QTcpSocket* nextConnection();

private:
    void incomingConnection(int socketDescriptor);
    QList<QTcpSocket*> sockets_;
    QMap<QTcpSocket*, int> status_;
    QThread thread_;

signals:
    void newConn();

public slots:
    void onNewConnection();


};

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void move();

    void send(const QByteArray& msg);
signals:

public slots:
    void onNewConnection();
    void onReadyRead();
    void onClose();

private:
    TcpServer server_;
    QThread thread_;

    QList<QTcpSocket*> sockets_;
};


#endif // SERVER_H
