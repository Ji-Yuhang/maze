#include "mazeview.h"

#include <QMouseEvent>
#include <assert.h>
#include "autofindpath.h"
MazeView::MazeView(QGraphicsView *parent) : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setBackgroundBrush(QPixmap(":/images/cheese.jpg"));
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);

    setScene(&scene_);
//    QGraphicsTextItem* textItem = scene_.addText("Game Begin");
    Role* role = new Role;
    scene_.addItem(role);
    roleList_.append(role);
    moveTimer_.setInterval(100);
    connect(&moveTimer_, SIGNAL(timeout()), this, SLOT(onMoveTimerTimeout()));


}

MazeView::~MazeView()
{

}

void MazeView::onMoveTimerTimeout()
{

}

void MazeView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    Role* role = roleList_.first();
    if (!role) return;

    QPoint ePos = event->pos();
    QPointF scenePos = mapToScene(ePos);

    AutoFindPath::FindPath(role,role->scenePos(),scenePos);

//    moveToPoint(role, scenePos);
}

void MazeView::moveToPoint(Role *role, QPointF pointF)
{
    assert(role);
    moveTimer_.start(100);
    moveRolePointF_ = pointF;
    role->setPos(pointF);
}

