#ifndef AUTOFINDPATH_H
#define AUTOFINDPATH_H

#include <QObject>
#include <QTimer>
#include <QPointF>
#include "role.h"
class AutoFindPath : public QObject
{
    Q_OBJECT
public:
    static void FindPath(Role* role, QPointF from, QPointF to);
    static QMap<Role*,AutoFindPath*> rolePathMap_;

    explicit AutoFindPath(QObject *parent = 0);
    ~AutoFindPath();
    void setRange(QPointF from, QPointF to);
    void setRole(Role* role);
    void start();
    void stop();
signals:

private slots:
    void onTimeout();
private:
    QTimer timer_;
    QPointF fromPointF_;
    QPointF toPointF_;
    QPointF tempPointF_;
    Role* role_;
    qreal pace_;
    qreal radius_;

};

#endif // AUTOFINDPATH_H
