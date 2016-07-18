#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

    void send(const QByteArray& msg);
signals:

public slots:
    void onNewConnection();
    void onReadyRead();
    void onClose();

private:
    QTcpServer server_;
    QList<QTcpSocket*> sockets_;
};

#endif // SERVER_H
