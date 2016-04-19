#include "circle.h"

circle::circle(QRectF rect, float x, float y, QGraphicsItem *it)
{
    rad=rect.height();
    shape = rect;
    center = QPointF(x,y);
    angle = 0;
    item = it;
}
