#include "object.h"

object::object()
{

}

void object::gravity(){
    velocity = velocity + QPointF(0,0.000001)*step;
    center=center+velocity*step;
    item->setPos(center);
}
