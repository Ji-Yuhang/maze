#ifndef MAZEVIEW_H
#define MAZEVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include "role.h"
#include "bullet.h"
#include <QTcpSocket>
#include <QGraphicsSimpleTextItem>
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
    void onReadyRead();
    void onTimeout();
protected:
    void drawForeground(QPainter *painter, const QRectF &rect);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event){}
    void mouseDoubleClickEvent(QMouseEvent *event){}
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event){}
    void mouseReleaseEvent(QMouseEvent *event){}

private:
    Role* findRole(const QString& token);
private:
    QGraphicsScene scene_;
    QList<Role*> roleList_;
    QTcpSocket* socket_;
    QTimer timer_;
    QGraphicsSimpleTextItem ms_;
//    QTimer moveTimer_;
//    QPointF moveRolePointF_;
};

#endif // MAZEVIEW_H
