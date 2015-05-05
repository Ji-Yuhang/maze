#ifndef MAZEVIEW_H
#define MAZEVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include "role.h"
class MazeView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MazeView(QGraphicsView *parent = 0);
    ~MazeView();

signals:

public slots:
private slots:
    void onMoveTimerTimeout();
protected:
    void keyPressEvent(QKeyEvent *event){}
    void keyReleaseEvent(QKeyEvent *event){}
    void mouseDoubleClickEvent(QMouseEvent *event){}
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event){}
    void mouseReleaseEvent(QMouseEvent *event){}
private:
    void moveToPoint(Role* role, QPointF pointF);
private:
    QGraphicsScene scene_;
    QList<Role*> roleList_;
    QTimer moveTimer_;
    QPointF moveRolePointF_;
};

#endif // MAZEVIEW_H
