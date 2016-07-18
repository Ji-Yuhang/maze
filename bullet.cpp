#include "bullet.h"
#include <QPainter>
Bullet::Bullet()
{
    freeze_ = false;
    setZValue(8);

}

void Bullet::setFreeze(bool freeze)
{
    freeze_ = true;

}

QRectF Bullet::boundingRect() const
{
    qreal penWidth = 1;
    qreal radius = 10;
    qreal diameter = 20;
    return QRectF(-radius - penWidth / 2, -radius - penWidth / 2,
                  diameter + penWidth, diameter + penWidth);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Bullet
    if (freeze_)
        painter->setBrush(Qt::red);
    else
        painter->setBrush(Qt::black);

    painter->drawRect(QRectF(-2, -2, 8, 8));

}


