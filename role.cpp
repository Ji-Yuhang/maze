#include "role.h"

Role::Role(QGraphicsItem *parent) : QGraphicsItem(parent)
{

}

Role::~Role()
{

}

QRectF Role::boundingRect() const
{
    qreal penWidth = 1;
    qreal radius = 10;
    qreal diameter = 20;
    return QRectF(-radius - penWidth / 2, -radius - penWidth / 2,
                  diameter + penWidth, diameter + penWidth);
}

void Role::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
}

