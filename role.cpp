#include "role.h"
#include <QGraphicsScene>
Role::Role(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    color_ = QColor(qrand() % 256, qrand() % 256, qrand() % 256);

    token_ = QUuid::createUuid().toString();
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
    // Body
    qreal mouseEyeDirection = eyeDirection_;
    painter->setBrush(color_);
    painter->drawEllipse(-10, -20, 20, 40);

    // Eyes
    painter->setBrush(Qt::white);
    painter->drawEllipse(-10, -17, 8, 8);
    painter->drawEllipse(2, -17, 8, 8);

    // Nose
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(-2, -22, 4, 4));

    // Pupils
    painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
    painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));

    // Ears
    painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
    painter->drawEllipse(-17, -12, 16, 16);
    painter->drawEllipse(1, -12, 16, 16);

    // Tail
    QPainterPath path(QPointF(0, 20));
    path.cubicTo(-5, 22, -5, 22, 0, 25);
    path.cubicTo(5, 27, 5, 32, 0, 30);
    path.cubicTo(-5, 32, -5, 42, 0, 35);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);}

