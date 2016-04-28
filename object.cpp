#include "object.h"

object::object()
{

}


void object::gravity(){
    velocity = velocity + QPointF(0,9.81)*step/10000;
}
void object::move(){
    center=center+velocity*step/1000;
    shape.translate(velocity*step/1000);
    item->setPos(center);
}

QPointF object::Icenter(){
    return center;
}

double object::Iw(){
    return W;
}

double object::Ii(){
    return I;
}

double object::Imass(){
    return mass;
}

QPointF object::Ivel(){
    return velocity;
}

QRectF object::Ishape(){
    return shape;
}

void object::apply_impulse(double x, double y, QPointF normal, double impulse){
  QPointF RA(x - center.x(), y - center.y());
  velocity.setX(velocity.x() + normal.x() / mass * impulse);
  velocity.setY(velocity.y() + normal.y() / mass * impulse);
  W += impulse * (normal.y() * RA.x() - normal.x() * RA.y())/I;
}
