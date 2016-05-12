#ifndef CIRCLE_H
#define CIRCLE_H
#include "object.h"

class circle : public object
{
private:
    double rad;
public:
    circle(QGraphicsRectItem* rect, float x, float y, QGraphicsItem *it, double r);
    double Irad();
};

#endif // CIRCLE_H
