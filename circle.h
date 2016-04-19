#ifndef CIRCLE_H
#define CIRCLE_H
#include "object.h"

class circle : public object
{
public:
    circle(QRectF rect, float x, float y, QGraphicsItem *it);
    int rad;
};

#endif // CIRCLE_H
