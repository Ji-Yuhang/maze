#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>

class Bullet : public QGraphicsObject
{
public:
    Bullet();
    void setFreeze(bool freeze);
    QRectF boundingRect() const;
protected:
    void paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget);
    bool freeze_;
};

#endif // BULLET_H
