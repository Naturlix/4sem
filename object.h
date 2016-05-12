#ifndef OBJECT_H
#define OBJECT_H
#include <QtWidgets>
#define scale 0.01
#define step 1/2000
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
    QGraphicsRectItem* shape;
public:
    void apply_impulse(double x, double y, QPointF normal, double impulse);
    bool isBorder = 0;
    double width,height;
    QGraphicsRectItem* Ishape();
    QPointF Icenter();
    QPointF Ivel();
    double Imass();
    double Ii();
    object();
    double Iw();
    double Iangle();
    void gravity();
    void move();
};

#endif // OBJECT_H
