#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "object.h"

class rectangle : public object
{
public:
    rectangle(QRectF, float x, float y, QGraphicsItem* it,bool brd);
    void gravity();
private:

    bool isBorder;
    int width;
    int height;
private slots:

};

#endif // RECTANGLE_H
