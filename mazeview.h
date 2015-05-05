#ifndef MAZEVIEW_H
#define MAZEVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include "role.h"
class MazeView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MazeView(QGraphicsView *parent = 0);
    ~MazeView();

signals:

public slots:
private:
    QGraphicsScene scene_;
    QList<Role*> roleList_;
};

#endif // MAZEVIEW_H
