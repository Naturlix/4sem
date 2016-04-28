#include "rectangle.h"


rectangle::rectangle(QRectF rect, float x, float y, QGraphicsItem *it, bool brd)
{
    isBorder = brd;
    width = rect.width();
    height = rect.height();
    shape = rect;
    center = QPointF(x+width/2,y+height/2);
    angle = 0;
    item = it;
    mass = (double) (width*height)/100;
    I = (double) (mass*(width*width+height*height)/120);
}

void rectangle::gravity(){
    if(!isBorder){
        velocity = velocity + QPointF(0,9.81)*step/10000;
    }
}

