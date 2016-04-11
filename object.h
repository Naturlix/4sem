#ifndef OBJECT_H
#define OBJECT_H
#include <QtWidgets>

#define step 1/24*1000
class object
{
protected:
    QPointF center;
    QPointF velocity;
    QPointF acceleration;
    double angle;
    QGraphicsScene* parent;
    QGraphicsItem* item;
public:
    object();
    void gravity();
};

#endif // OBJECT_H
