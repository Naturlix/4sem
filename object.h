#ifndef OBJECT_H
#define OBJECT_H
#include <QtWidgets>

#define step 1/100*1000
class object
{
protected:
    QPointF center;
    QPointF velocity;
    QPointF acceleration;
    double angle;
    QGraphicsScene* parent;
    QGraphicsItem* item;
    QRectF shape;
public:
    object();
    void gravity();
};

#endif // OBJECT_H
