#include "object.h"

object::object()
{

}

void object::gravity(){
    velocity = velocity + QPointF(0,9.81)*step/10000;
    center=center+velocity*step/1000;
    shape.translate(velocity*step);
    item->setPos(center);
}
