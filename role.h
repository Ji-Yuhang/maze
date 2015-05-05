#ifndef ROLE_H
#define ROLE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
class Role : public QGraphicsItem
{

public:
    explicit Role(QGraphicsItem *parent = 0);
    ~Role();
    QRectF boundingRect() const;
    void paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget);
};

#endif // ROLE_H
