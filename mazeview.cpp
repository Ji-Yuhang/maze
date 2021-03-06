#include "mazeview.h"
#include <QtMath>

#include <QMouseEvent>
#include <assert.h>
#include <QGraphicsBlurEffect>
#include "autofindpath.h"
#include <QPropertyAnimation>
#include <QDataStream>
#include <QDateTime>
MazeView::MazeView(QGraphicsView *parent) : QGraphicsView(parent),socket_(new QTcpSocket)
{
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QPixmap(":/images/cheese.jpg"));
//    setForegroundBrush(Qt::black);

    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
//    setDragMode(QGraphicsView::RubberBandDrag);
    scene_.setSceneRect(0,0,1000,1000);
    setScene(&scene_);
    setGraphicsEffect(new QGraphicsBlurEffect);
//    QGraphicsTextItem* textItem = scene_.addText("Game Begin");
    Role* role = new Role;
    scene_.addItem(role);
    ms_.setZValue(8);
    ms_.setPos(mapToScene(0,0));
    scene_.addItem(&ms_);
    roleList_.append(role);
//    moveTimer_.setInterval(100);
//    connect(&moveTimer_, SIGNAL(timeout()), this, SLOT(onMoveTimerTimeout()));

    connect(&timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));

}

MazeView::~MazeView()
{

}

void MazeView::setServerIp(QHostAddress address, qint16 port)
{
//    mazeview_->setServerIp(address, port);
    socket_->connectToHost(address,port);
    socket_->waitForConnected();
    connect(socket_, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    timer_.start(1000);
}
void MazeView::onMoveTimerTimeout()
{

}

void MazeView::onReadyRead()
{
    if (socket_->bytesAvailable() < 1) return;
    QByteArray block = socket_->readAll();
    QDataStream stream(&block, QIODevice::ReadOnly);
    QString type;
    QString who;
    QMap<QString,QVariant> data;
    stream >> type >> who >> data;
    qDebug() << "view receive: "<< type << who << data;

//    QString type = data["type"];
    if (type == "move") {
        QPointF from = data["from"].toPointF();
        QPointF to = data["to"].toPointF();


        Role* role = findRole(who);

//        if (!role) return;


        if (role) {
            qDebug() << "FindPath "<< role << from << to;

            AutoFindPath::FindPath(role,from,to);
        }
    } else if (type == "heart") {
        QDateTime time = data["now"].toDateTime();
        QDateTime now = QDateTime::currentDateTime();
        qint64 ms = time.msecsTo(now);
        ms_.setText(QString("%1 ms").arg(ms));
        ms_.setPos(mapToScene(0,0));
        qDebug() << "ms : " << now << " - "<<time <<" = "<< ms;

    }

}

void MazeView::onTimeout()
{
    QByteArray block;
    QDataStream s(&block, QIODevice::WriteOnly);
    Role* role = roleList_.first();

    QMap<QString, QVariant> data;
    data["now"] = QDateTime::currentDateTime();
    s << QString("heart") << role->token()<<data;
    socket_->write(block);

}

void MazeView::drawForeground(QPainter *painter, const QRectF &rect)
{
//    Role* role = roleList_.first();
//    if (!role) return;

//    QRectF roleRect = role->boundingRect();
//    roleRect.adjust(-400,-400,800,800);

//    painter->setBrush(Qt::black);
//    QRectF upRect(0,0,rect.width(),roleRect.height());
//    QRectF downRect(0,roleRect.bottom(), rect.width(),rect.height()- roleRect.bottom());

//    painter->drawRect(upRect);
//    painter->drawRect(downRect);
}

void MazeView::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
//    if (key == Qt::Key_F1) ensureVisible(roleList_.first());
    Role* role = roleList_.first();

    if (key == Qt::Key_F1) {
        if (role) centerOn(role);
    } else if (key == Qt::Key_Q) {
        // 发射普通子弹
        // bullet
        Bullet* bullet = new Bullet;
        bullet->setPos(role->pos());
        QPropertyAnimation *animation = new QPropertyAnimation(bullet, "pos");
        animation->setDuration(100);
        animation->setStartValue(role->pos());
        animation->setEndValue(mapToScene(mapFromGlobal(QCursor::pos())));
        scene_.addItem(bullet);
        animation->start();


    } else if (key == Qt::Key_W) {
        // 晕人

//        QPointF line = mapToScene(mapFromGlobal(QCursor::pos())) - role->pos();
//        double n = qPow(line.rx(),2) + qPow(line.ry(),2);
//        double m = n * qTan(qDegreesToRadians(role->rotation()));
//        double x = m * qCos(qDegreesToRadians(role->rotation()));
//        double y = m * qSin(qDegreesToRadians(role->rotation()));

        {
            // bullet 1
            Bullet* bullet = new Bullet;
            bullet->setFreeze(true);
            bullet->setPos(role->pos());
            QPropertyAnimation *animation = new QPropertyAnimation(bullet, "pos");
            animation->setDuration(1000);
            animation->setStartValue(role->pos());
            animation->setEndValue(mapToScene(mapFromGlobal(QCursor::pos())));
            scene_.addItem(bullet);
            animation->start();
        }
//        {
//            // bullet 2
//            Bullet* bullet = new Bullet;
//            bullet->setPos(role->pos());
//            QPropertyAnimation *animation = new QPropertyAnimation(bullet, "pos");
//            animation->setDuration(1000);
//            animation->setStartValue(role->pos());
//            animation->setEndValue(mapToScene(mapFromGlobal(QCursor::pos())) - QPointF(x,y));
//            scene_.addItem(bullet);
//            animation->start();
//        }
//        {
//            // bullet 3
//            Bullet* bullet = new Bullet;
//            bullet->setPos(role->pos());
//            QPropertyAnimation *animation = new QPropertyAnimation(bullet, "pos");
//            animation->setDuration(1000);
//            animation->setStartValue(role->pos());
//            animation->setEndValue(mapToScene(mapFromGlobal(QCursor::pos())) + QPointF(x,y));
//            scene_.addItem(bullet);
//            animation->start();
//        }

    } else if (key == Qt::Key_E) {
        // 闪烁到指定位置
         if (AutoFindPath::rolePathMap_.contains(role)) {
             AutoFindPath::rolePathMap_.value(role)->stop();
         }
        role->setPos(mapToScene(mapFromGlobal(QCursor::pos())));
        role->setVisible(true);
        role->scene()->invalidate();


    } else if (key == Qt::Key_R) {
        // 隐身

    } else if (key == Qt::Key_D) {

    } else if (key == Qt::Key_F) {

    }


}

void MazeView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    if (event->button() & Qt::RightButton) {
        Role* role = roleList_.first();
        if (!role) return;

        QPoint ePos = event->pos();
        QPointF scenePos = mapToScene(ePos);

        QByteArray sendBlock;
        QDataStream os(&sendBlock, QIODevice::WriteOnly);
        QMap<QString, QVariant> data;
        data["from"] = role->pos();
        data["to"] = scenePos;

        os << QString("move") << role->token()<<data;
        qDebug() << "view send:" << "move" <<role->token() << data;
        socket_->write(sendBlock);
    }

}

Role *MazeView::findRole(const QString& token)
{
    Q_FOREACH(Role* role, roleList_) {
        if (role->token() == token) {
            return role;
        }
    }
    return NULL;
}

