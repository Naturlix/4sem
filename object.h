#ifndef OBJECT_H
#define OBJECT_H
#include <QtWidgets>

#define step 1/100*1000
class object
{
protected:
    QPointF center;
    QPointF velocity;
    double mass;
    double W;
    double I;
    double angle;
    QGraphicsScene* parent;
    QGraphicsItem* item;
    QRectF shape;
public:
    void apply_impulse(double x, double y, QPointF normal, double impulse);
    QRectF Ishape();
    QPointF Icenter();
    QPointF Ivel();
    double Imass();
    double Ii();
    object();
    double Iw();
    void gravity();
    void move();
};

#endif // OBJECT_H
