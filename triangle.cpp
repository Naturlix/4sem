#include "triangle.h"

triangle::triangle(QRectF rect, float x, float y, QGraphicsItem *it)
{
    a=rect.width();
    shape = rect;
    center = QPointF(x,y);
    angle = 0;
    item = it;
}
