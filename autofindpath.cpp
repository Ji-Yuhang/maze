#include "autofindpath.h"
#include <QtMath>
#include <QDebug>
QMap<Role*,AutoFindPath*> AutoFindPath::rolePathMap_;

AutoFindPath::AutoFindPath(QObject *parent) : QObject(parent)
{
    pace_ = 5;
    radius_ = pace_ - 1;
    timer_.setInterval(20);
    connect(&timer_, SIGNAL(timeout()), this, SLOT(onTimeout()));

}

AutoFindPath::~AutoFindPath()
{

}

void AutoFindPath::setRange(QPointF from, QPointF to)
{
    fromPointF_ = from;
    toPointF_ = to;
}

void AutoFindPath::setRole(Role *role)
{
    role_ = role;
}

void AutoFindPath::start()
{
    tempPointF_ = fromPointF_;
    timer_.start();
}

void AutoFindPath::stop()
{
    timer_.stop();
}

void AutoFindPath::FindPath(Role *role, QPointF from, QPointF to)
{
    if (rolePathMap_.contains(role)) {
        AutoFindPath* p = rolePathMap_.value(role);
        p->stop();
        p->deleteLater();
        rolePathMap_.remove(role);
    }
    AutoFindPath * path = new AutoFindPath;
    rolePathMap_.insert(role,path);

    path->setRange(from, to);
    path->setRole(role);
    path->start();
}

void AutoFindPath::onTimeout()
{
    qreal x1 = tempPointF_.x();
    qreal y1 = tempPointF_.y();

    qreal x2 = toPointF_.x();
    qreal y2 = toPointF_.y();

    qreal xNegative = (x2 - x1) > 0 ? 1.0 : -1.0;
    qreal yNegative = (y2 - y1) > 0 ? 1.0 : -1.0;

    xNegative = 1.0;
    yNegative = 1.0;
    qreal fromDistance = qSqrt(qPow(x2-x1, 2) + qPow(y2-y1, 2));

    qreal xdif = xNegative * pace_ * (x2 - x1) / fromDistance;
    qreal ydif = yNegative * pace_ * (y2 - y1) / fromDistance;

    qreal x3 = x1 + xdif;
    qreal y3 = y1 + ydif;
    qreal toDistance = qSqrt(qPow(x3-x2, 2) + qPow(y3-y2, 2));

//    qDebug() << tempPointF_ << toPointF_<< xNegative << yNegative<<fromDistance<<toDistance<< xdif << ydif;

    tempPointF_.setX(x3);
    tempPointF_.setY(y3);

    if (toDistance <= radius_) {
//        qDebug() << "STOP!";
        timer_.stop();
        if (rolePathMap_.contains(role_)) {
            rolePathMap_.remove(role_);
        }
        this->deleteLater();
    }

    qreal ration = qAtan2(ydif, xdif);
    qreal degree = qRadiansToDegrees(ration);
    qDebug() << ration << degree;
    role_->setRotation(degree + 90);
//    setRotation(rotation() + dx);

    role_->setPos(tempPointF_);
//    role_->setEyeDirection();

    role_->update();
}

