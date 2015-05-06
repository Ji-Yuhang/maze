#include "mazeview.h"

#include <QMouseEvent>
#include <assert.h>
#include <QGraphicsBlurEffect>
#include "autofindpath.h"
MazeView::MazeView(QGraphicsView *parent) : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QPixmap(":/images/cheese.jpg"));
//    setForegroundBrush(Qt::black);

    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
//    setDragMode(QGraphicsView::RubberBandDrag);
    scene_.setSceneRect(0,0,10000,10000);
    setScene(&scene_);
    setGraphicsEffect(new QGraphicsBlurEffect);
//    QGraphicsTextItem* textItem = scene_.addText("Game Begin");
    Role* role = new Role;
    scene_.addItem(role);
    roleList_.append(role);
//    moveTimer_.setInterval(100);
//    connect(&moveTimer_, SIGNAL(timeout()), this, SLOT(onMoveTimerTimeout()));


}

MazeView::~MazeView()
{

}

void MazeView::onMoveTimerTimeout()
{

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
    if (key == Qt::Key_F1) {
        Role* role = roleList_.first();
        if (role) centerOn(role);
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

        AutoFindPath::FindPath(role,role->scenePos(),scenePos);
    }

}

