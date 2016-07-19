#include "server.h"
#include <QMessageBox>
#include <QDebug>

TcpServer::TcpServer()
//    port_(port)
{
//    connect(&server_, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

}

TcpServer::~TcpServer()
{
    thread_.terminate();

}


void TcpServer::start()
{
//    qDebug() << "server start's thread" << this->thread();
//    if (!this->listen(QHostAddress::Any,port_)) {
//        ERROR2("Server bind port error:",port_);
//    }
    thread_.start();

}

QTcpSocket *TcpServer::nextConnection()
{
    QMap<QTcpSocket*, int>::iterator it = status_.begin();
    for (; it != status_.end(); ++it) {
        if (it.value() == 1) {
            it.value() = 2;
            return it.key();
        }
    }
    return NULL;
}

void TcpServer::incomingConnection(int socketDescriptor)
{

    qDebug() << "incomingConnection" << socketDescriptor;
    QTcpSocket * socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    socket->moveToThread(&thread_);
    sockets_.append(socket);
    status_.insert(socket, 1);

    Q_EMIT newConn();
}

void TcpServer::onNewConnection()
{

//    DataThread* thread = new DataThread(server_.nextPendingConnection());
//    LOG1("Server get a new connection, start a new thread");
    qDebug() << "new connection's thread:"<< this->thread();
//    qDebug() << "DataThread* thread:" << thread->thread();
//    thread->socket_->moveToThread(thread);
//    thread->start();
//    boost::function<void()> f = boost::bind(&DataThread::run,thread);
//    boost::thread th(f);
//    QThread th;
//    thread->moveToThread(&th);
//    thread->run();
//    th.start();
//    th.wait();
}
Server::Server(QObject *parent) : QObject(parent)
{

    server_.start();
    bool s = server_.listen(QHostAddress::Any, 4321);
    if (!s) {
        QMessageBox::warning(0,"无法建立服务器","监听4321端口错误");
    }
    connect(&server_, SIGNAL(newConn()), this, SLOT(onNewConnection()));

}

void Server::move()
{
    server_.moveToThread(&thread_);
    thread_.start();
}

void Server::send(const QByteArray &msg)
{
    Q_FOREACH(QTcpSocket* s, sockets_) {
        s->write(msg);
    }
}

void Server::onNewConnection()
{

    QTcpSocket* socket = server_.nextConnection();
    qDebug() << "onNewConnection thread:"<< this->thread();
    qDebug() << "new socket thread:" << socket->thread();
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
    QMap<QString,QVariant> data;
    stream >> type >> who >> data;
    qDebug() << "server receive: "<< type << who << data;

//    QString type = data["type"];
    if (type == "move") {
        QPointF from = data["from"].toPointF();
        QPointF to = data["to"].toPointF();

        QByteArray sendBlock;
        QDataStream os(&sendBlock, QIODevice::WriteOnly);
        os <<QString("move") << who <<data;

        qDebug() << "server send: "<< type << who << data;
        send(sendBlock);
    } else if (type == "heart") {
        send(block);
    }

}

void Server::onClose()
{
    QTcpSocket* s = qobject_cast<QTcpSocket*>(sender());
    sockets_.removeOne(s);

}
