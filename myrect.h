#ifndef MYRECT_H
#define MYRECT_H

#include <QtWidgets>

class MyRect : public QGraphicsRectItem
{
public:
    QPointF topLeft();
    QPointF topRight();
    QPointF bottomLeft();
    QPointF bottomRight();
    double heigh;
    double width;
};

#endif // MYRECT_H

QPointF MyRect::topLeft(){
    QPointF diag(this->width,this->heigh);
    return QPointF(x-width*rotation,y+heigh*rotation)





}
