#include "server.h"
#include <QMessageBox>
#include <QDebug>
Server::Server(QObject *parent) : QObject(parent)
{
    bool s = server_.listen(QHostAddress::Any, 4321);
    if (!s) {
        QMessageBox::warning(0,"无法建立服务器","监听4321端口错误");
    }
    connect(&server_, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

}

void Server::send(const QByteArray &msg)
{
    Q_FOREACH(QTcpSocket* s, sockets_) {
        s->write(msg);
    }
}

void Server::onNewConnection()
{
    QTcpSocket* socket = server_.nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(aboutToClose()), this, SLOT(onClose()));

    sockets_.append(socket);

}

void Server::onReadyRead()
{
    QTcpSocket* s = qobject_cast<QTcpSocket*>(sender());
    if (s->bytesAvailable() < 1) return;
    QByteArray block = s->readAll();
    QDataStream stream(&block,QIODevice::ReadOnly);
    QString type;
    QString who;
    QMap<QString,QPointF> data;
    stream >> type >> who >> data;
    qDebug() << "server receive: "<< block<< type << who << data;

//    QString type = data["type"];
    if (type == "move") {
        QPointF from = data["from"];
        QPointF to = data["to"];

        QByteArray sendBlock;
        QDataStream os(&sendBlock, QIODevice::WriteOnly);
        os <<QString("move") << who <<data;

        qDebug() << "server send: "<< type << who << data;
        send(sendBlock);
    }

}

void Server::onClose()
{
    QTcpSocket* s = qobject_cast<QTcpSocket*>(sender());
    sockets_.removeOne(s);

}
