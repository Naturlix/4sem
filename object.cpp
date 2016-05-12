#include "object.h"

object::object()
{

}


void object::gravity(){
    if(!isBorder){
        apply_impulse(center.x(),center.y(),QPointF(0,1),mass*100*step);
    }
}

void object::move(){
        center=center+velocity*step;
        angle += W*step;
        shape->setPos(shape->pos() + velocity*step);
        shape->setTransformOriginPoint(center);
        shape->setRotation(shape->rotation() + W*step);
        item->moveBy(velocity.x()*step/scale,velocity.y()*step/scale);
        item->setTransformOriginPoint(center/scale);
        item->setRotation(shape->rotation());
}

QPointF object::Icenter(){
    return center;
}

double object::Iangle(){
    return angle;
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

QGraphicsRectItem* object::Ishape(){
    return shape;
}

void object::apply_impulse(double x, double y, QPointF normal, double impulse){
  QPointF RA(x - center.x(), y - center.y());
  velocity.setX(velocity.x() + normal.x() / mass * impulse);
  velocity.setY(velocity.y() + normal.y() / mass * impulse);
  W += impulse * (normal.y() * RA.x() - normal.x() * RA.y())/I;
}
