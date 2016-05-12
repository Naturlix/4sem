#include "rectangle.h"


rectangle::rectangle(QGraphicsRectItem* rect, float x, float y, QGraphicsItem *it, bool brd, double a, double b)
{
    isBorder = brd;
    width = a;
    height = b;
    velocity=QPointF(0,0);
    shape = rect;
    center = QPointF(x,y);
    angle = 0;
    item = it;
    W=0;
    mass = (double) (width*height);
    I = (double) (mass*(width*width+height*height))/12;
}



