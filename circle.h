#ifndef CIRCLE_H
#define CIRCLE_H
#include "object.h"

class circle : public object
{
private:
    double rad;
public:
    circle(QRectF rect, float x, float y, QGraphicsItem *it);
    double Irad();
    void move();
};

#endif // CIRCLE_H
