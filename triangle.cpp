#include "triangle.h"

triangle::triangle(QGraphicsRectItem *rect, float x, float y, QGraphicsItem *it,double h)
{
    a=h;
    shape = rect;
    center = QPointF(x,y);
    angle = 0;
    item = it;
}
