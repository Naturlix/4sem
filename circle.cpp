#include "circle.h"

circle::circle(QGraphicsRectItem *rect, float x, float y, QGraphicsItem *it,double r)
{
    rad=r;
    width = r;
    height = r;
    shape = rect;
    center = QPointF(x,y);
    velocity=QPointF(0,0);
    angle = 0;
    item = it;
    mass = 3.1415*rad*rad;
    I = mass*rad*rad/2;
    W = 0;
}

double circle::Irad(){
    return rad;
}
