#include "login.h"
#include "ui_login.h"

#include <QMessageBox>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login),
    main_(0)
{
    ui->setupUi(this);
    bool bs = socket_.bind(4444);
//    socket_.joinMulticastGroup(QHostAddress::AnyIPv4);
    bool cs = connect(&socket_, SIGNAL(readyRead()), this, SLOT(onRead()));
    QHostAddress local = getIP();

}

Login::~Login()
{
    delete ui;
}

void Login::on_search_clicked()
{

//    knownHosts_.clear();
    QByteArray block;
    QDataStream s(&block, QIODevice::WriteOnly);
    s << QString("search");
    socket_.writeDatagram(block,QHostAddress::Broadcast, 4444);
    qDebug() <<"UDP send:" << block.size() << block;

}

void Login::on_create_clicked()
{

}

void Login::onRead()
{
    qDebug() << "onRead UDP";
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

        if (type == "search") {
            QByteArray block;
            QDataStream s(&block, QIODevice::WriteOnly);
            s << QString("response");
            socket_.writeDatagram(block,QHostAddress::Broadcast, 4444);

        } else if (type == "response") {
            if (!address.isLoopback()) {
                if (!knownHosts_.contains(address.toIPv4Address())) {
                    knownHosts_.insert(address.toIPv4Address(), address);

                    while (ui->tableWidget->rowCount() > 0) {
                        ui->tableWidget->removeRow(0);
                        //                    ui->tableWidget->clear();
                    }

                    ui->tableWidget->setRowCount(knownHosts_.size());
                    QMap<quint32, QHostAddress>::iterator it = knownHosts_.begin();
                    for (int row = 0; it != knownHosts_.end(); ++it) {
                        {
                            QTableWidgetItem* item = new QTableWidgetItem;
                            item->setText(it.value().toString());
                            ui->tableWidget->setItem(row,0,item);
                        }
                        {
                            QTableWidgetItem* item = new QTableWidgetItem;
                            item->setText("坦克大战");
                            ui->tableWidget->setItem(row,1,item);
                        }
                        {
                            QTableWidgetItem* item = new QTableWidgetItem;
                            item->setText("未知");
                            ui->tableWidget->setItem(row,2,item);
                        }
                        {
                            QTableWidgetItem* item = new QTableWidgetItem;
                            item->setText("无");
                            ui->tableWidget->setItem(row,3,item);
                        }
                        {
                            QTableWidgetItem* item = new QTableWidgetItem;
                            item->setText("1 ms");
                            ui->tableWidget->setItem(row,4,item);
                        }

                        {
                            QPushButton* item = new QPushButton;
                            item->setText("加入游戏");
                            item->setProperty("ip", it.key());
                            connect(item, SIGNAL(clicked(bool)), this, SLOT(onJoin()));
                            ui->tableWidget->setCellWidget(row,5, item);
                        }


                        ++row;
                    }


                    ui->tableWidget->resizeColumnsToContents();
                }
            }
        }
    }
//    QByteArray block = socket_.readDatagram();
    //    qDebug() << "UDP read : "<< block;
}

void Login::onJoin()
{
    QMessageBox::information(0,"success","加入游戏成功");
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    main_ = new MainWindow;
    serverIp_ = knownHosts_.value(button->property("ip").toInt());
    main_->setServerIp(serverIp_, 4321);
    this->hide();
    main_->show();
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
