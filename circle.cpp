#include "circle.h"

circle::circle(QRectF rect, float x, float y, QGraphicsItem *it)
{
    rad=rect.height()/2;
    shape = rect;
    center = QPointF(x,y);
    angle = 0;
    item = it;
    mass = 3.1415*rad*rad/10000;
    I = 1/2*mass*rad*rad/10000;
}

double circle::Irad(){
    return rad;
}

void circle::move(){
    center=center+velocity*step/1000;
    shape.translate(velocity*step/1000);
    item->moveBy(velocity.x()*step/1000,velocity.y()*step/1000);
}
