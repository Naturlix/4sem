#include <QtWidgets>


bool CircleIntersects(QPointF center, double R, QPointF A, QPointF B, QPointF* Z)
{

    float x01=A.x()-center.x();
    float y01=A.y()-center.y();
    float x02=B.x()-center.x();
    float y02=B.y()-center.y();

    float dx=x02-x01;
    float dy=y02-y01;

    float a=dx*dx+dy*dy;
    float b=2.0f*(x01*dx+y01*dy);
    float c=x01*x01+y01*y01-R*R;
    *Z = QPointF(center.x()+R*dy/sqrt(a),center.y()+R*dx/sqrt(a));

    if(-b<0)return (c<0);
    if(-b<(2.0f*a))return (4.0f*a*c-b*b<0);
    return (a+b+c<0);

}
