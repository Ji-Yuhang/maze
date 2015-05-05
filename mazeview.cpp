#include "mazeview.h"

MazeView::MazeView(QGraphicsView *parent) : QGraphicsView(parent)
{
    setScene(&scene_);
    QGraphicsTextItem* textItem = scene_.addText("Game Begin");
    Role* role = new Role;
    scene_.addItem(role);
    roleList_.append(role);


}

MazeView::~MazeView()
{

}

