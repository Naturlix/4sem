#include <QtWidgets>


bool CircleIntersects(QPointF center, double R, QPointF A, QPointF B, QPointF* Z)
{
    double sina, cosa,k,p,r;
    float x01=A.x()-center.x();
    float y01=A.y()-center.y();
    float x02=B.x()-center.x();
    float y02=B.y()-center.y();

    float dx=x02-x01;
    float dy=y02-y01;



    float a=dx*dx+dy*dy;

    float b=2.0f*(x01*dx+y01*dy);
    float c=x01*x01+y01*y01-R*R;

    if (dx!=0){
        k = dy/dx;
        p = A.y()-k*A.x();
        r = (-k*center.x()+center.y()-p)/sqrt(k*k+1);
        if(r<0) r*=-1;
        sina = dy/sqrt(a);
        cosa = -dx/sqrt(a);
    }else{
        sina = -1;
        cosa = 0;
        r = center.x()-A.x();
        if(r<0) r*=-1;
    }
    if(r>=R/4){
        if (center.y()-k*center.x()-p > 0){
            *Z = QPointF(center.x()+r*sina,center.y()+r*cosa);
        }else{
            *Z = QPointF(center.x()-r*sina,center.y()-r*cosa);
        }
    }else{
        return false;
    }
    if(-b<0)return (c<0);
    if(-b<(2.0f*a))return (4.0f*a*c-b*b<0);
    return (a+b+c<0);

}
double operator*(QPointF a, QPointF b){
    return a.x()*b.x()+a.y()*b.y();
}

bool are_crossing(QPointF v11, QPointF v12, QPointF v21, QPointF v22, QPointF* crossing){
    double k1 = (v11.y()-v12.y())/(v11.x()-v12.x());
    double c1 = v11.y()-k1*v11.x();

    double k2 = (v21.y()-v22.y())/(v21.x()-v22.x());
    double c2 = v21.y()-k2*v21.x();

    double p11 = v21.y()-k1*v21.x()-c1;
    double p12 = v22.y()-k1*v22.x()-c1;
    double p21 = v11.y()-k2*v11.x()-c2;
    double p22 = v12.y()-k2*v12.x()-c2;
    double x = (c2-c1)/(k1-k2);
    double y = k1*x+c1;

    if(p11*p12<=0 && p21*p22<=0){
        *crossing = QPointF(x,y);
        return true;
    }else{
        *crossing = QPointF(0,0);
        return false;
    }
}
