#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "object.h"

class rectangle : public object
{
public:
    rectangle(QGraphicsRectItem* rect, float x, float y, QGraphicsItem* it, bool brd, double a, double b);
private slots:

};

#endif // RECTANGLE_H
