#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "object.h"
#define Xrez 1360
#define Yrez 760
class triangle : public object
{
public:
    triangle(QRectF rect, float x, float y, QGraphicsItem *it);
private:
    int a;
};

#endif // TRIANGLE_H
