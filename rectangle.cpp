#include "rectangle.h"


rectangle::rectangle(QRectF rect, float x, float y, QGraphicsItem *it, bool brd)
{
    isBorder = brd;
    width = rect.width();
    height = rect.height();
    shape = rect ;
    center = QPointF(x,y);
    angle = 0;
    item = it;
}

void rectangle::gravity(){
    if(!isBorder){
        velocity = velocity + QPointF(0,9.81)*step/10000;
        center=center+velocity*step/1000;
        shape.translate(velocity*step);
        item->setPos(center);
    }
}
