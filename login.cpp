#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    socket_.bind(4444);
//    socket_.joinMulticastGroup(QHostAddress::AnyIPv4);
    connect(&socket_, SIGNAL(readyRead()), this, SLOT(onRead()));
    QHostAddress local = getIP();

}

Login::~Login()
{
    delete ui;
}

void Login::on_search_clicked()
{

    QByteArray block;
    QDataStream s(&block, QIODevice::WriteOnly);
    s << QString("search");
//    socket_.write(block);
    socket_.writeDatagram(block,QHostAddress::Broadcast, 4444);

}

void Login::on_create_clicked()
{

}

void Login::onRead()
{
    QHostAddress local = getIP();
    while (socket_.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket_.pendingDatagramSize());

        QHostAddress address;
        quint16 port;
        socket_.readDatagram(datagram.data(), datagram.size(),&address, &port);

        QDataStream s(&datagram, QIODevice::ReadOnly);
        QString type;
        s >> type;
        qDebug() << "UDP read : "<< datagram.data() << type << address << port << (address.toIPv4Address() == local.toIPv4Address());
        qDebug() << local<<local.toIPv4Address() << address.toIPv4Address() << (local.toIPv4Address() == address.toIPv4Address());


    }
//    QByteArray block = socket_.readDatagram();
//    qDebug() << "UDP read : "<< block;
}

// 获取ip地址，获取本机ip地址(其协议为ipv4的ip地址)
QHostAddress Login::getIP()
{
    //QList是Qt中一个容器模板类，是一个数组指针？
    QList<QHostAddress> list = QNetworkInterface::allAddresses();//此处的所有地址是指ipv4和ipv6的地址
    //foreach (variable, container),此处为按照容器list中条目的顺序进行迭代
    foreach (QHostAddress address, list) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback() ) {
            qDebug() << "allAddresses"<< address << address.toIPv4Address() << address.isLoopback();
            return address;
        }
    }
    return QHostAddress();
}
