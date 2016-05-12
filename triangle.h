#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "object.h"
#define Xrez 1360
#define Yrez 760
class triangle : public object
{
public:
    triangle(QGraphicsRectItem* rect, float x, float y, QGraphicsItem *it, double h);
private:
    int a;
};

#endif // TRIANGLE_H
