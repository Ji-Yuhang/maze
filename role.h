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
    void setEyeDirection(qreal d) {eyeDirection_ = d;}

    QRectF boundingRect() const;
protected:
    void paint(QPainter *painter,
                              const QStyleOptionGraphicsItem *option,
                              QWidget *widget);
private:
    QColor color_;
    qreal eyeDirection_;
//    void moveToPoint();
};

#endif // ROLE_H
