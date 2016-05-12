#include "widget.h"
#include "ui_widget.h"
#include "geometry.cpp"
#define bounce 0.1
Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene,this);
    view->setFixedSize(1010,710);
    view->setSceneRect(0,0,1000,700);
    view->show();
    root = new list();
    next=root;
    placeborders();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(addtime()));
    ui->setupUi(this);
    timer->start(1/fps*1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::addtime(){
    frame();
    timer->start(1/fps*1000);
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    int i = rand()%2+1;
    if(i == 1) spawnrect(e->localPos());
    if(i == 2) spawncirc(e->pos());
    //if(i == 3) spawntriang(e->pos());
}

void Widget::collision(list* p1, list* p2){
    double archimed = 10;
    rectangle* rect1 = NULL;
    rectangle* rect2 = NULL;
    triangle* triang1 = NULL;
    triangle* triang2 = NULL;
    circle* circ1 = NULL;
    circle* circ2 = NULL;
    QPointF Z=QPointF(0,0);
    if (p1->nValue1 != NULL) rect1=p1->nValue1;
    if (p1->nValue2 != NULL) triang1=p1->nValue2;
    if (p1->nValue3 != NULL) circ1=p1->nValue3;

    if (p2->nValue1 != NULL){
        if(rect1 == NULL){ rect1=p2->nValue1; }else{ rect2=p2->nValue1; }
    }
    if (p2->nValue2 != NULL){
        if(triang1 == NULL){ triang1=p2->nValue2; }else{ triang2=p2->nValue2; }
    }
    if (p2->nValue3 != NULL){
        if(circ1 == NULL){ circ1=p2->nValue3; }else{ circ2=p2->nValue3; }
    }
    // Круг и Круг
    if(circ1!= NULL && circ2 != NULL){
        QPointF check;
        check = circ1->Icenter()-circ2->Icenter();
        if(sqrt(check*check) <= circ1->Irad()+circ2->Irad()){
            Z = QPointF(0,0);
            QPointF R = circ1->Icenter() - circ2->Icenter();
            Z = circ1->Icenter() + R/sqrt(R*R)*circ1->Irad();
            QPointF n1 = circ1->Icenter()-circ2->Icenter();
            QPointF n2 = -1*n1;
            double w1 = n1*(Z-circ1->Icenter());
            double w2 = n2*(Z-circ2->Icenter());
            double a = n1*circ1->Ivel()+n2*circ2->Ivel()+w1*circ1->Iw()+w2*circ2->Iw();
            double c = (1+bounce)*a;
            double b = n1*n1/circ1->Imass()+w1*w1/circ1->Ii()+n2*n2/circ2->Imass()+w2*w2/circ2->Ii();
            double impulse;
            double l = (circ1->Irad()+circ2->Irad()-sqrt(R*R))*archimed;
            if(-c/b < 0){impulse = l;} else {impulse = -c/b+l;}
            circ1->apply_impulse(Z.x(),Z.y(),Z-circ1->Icenter(),impulse);
            circ2->apply_impulse(Z.x(),Z.y(),Z-circ2->Icenter(),-impulse);
        }
    }
    // Прямоугольник и круг
    if(rect1!= NULL && circ1 != NULL){
        bool key;
        Z = QPointF(0,0);
        double w = rect1->width/2;
        double h = rect1->height/2;
        int i;
        double alpha = rect1->Ishape()->rotation()/180*3.1415;
        QPointF Ra = QPointF(rect1->Icenter().x()-w*cos(alpha)+h*sin(alpha),rect1->Icenter().y()-w*sin(alpha)-h*cos(alpha));
        QPointF Rb = QPointF(rect1->Icenter().x()+w*cos(alpha)+h*sin(alpha),rect1->Icenter().y()+w*sin(alpha)-h*cos(alpha));
        QPointF Rc = QPointF(rect1->Icenter().x()+w*cos(alpha)-h*sin(alpha),rect1->Icenter().y()+w*sin(alpha)+h*cos(alpha));
        QPointF Rd = QPointF(rect1->Icenter().x()-w*cos(alpha)-h*sin(alpha),rect1->Icenter().y()-w*sin(alpha)+h*cos(alpha));
        QPointF R[8] = {Ra,Rb,Rb,Rc,Rd,Rc,Rd,Ra};
        for(i=0;i<8;i+=2){
            key = CircleIntersects(circ1->Icenter(), circ1->Irad(), R[i],R[i+1], &Z);
            if(key){
                QPointF n1 = circ1->Icenter()-Z;
                QPointF n2 = -1*n1;
                double w1 = n1*(Z-circ1->Icenter());
                double w2 = n2*(Z-rect1->Icenter());
                double a = n1*circ1->Ivel()+n2*rect1->Ivel()+w1*circ1->Iw()+w2*rect1->Iw();
                double c = (1+bounce)*a;
                double b = n1*n1/circ1->Imass()+w1*w1/circ1->Ii()+n2*n2/rect1->Imass()+w2*w2/rect1->Ii();
                double impulse;
                double l = (circ1->Irad()-sqrt(n1*n1))*archimed;
                if(-c/b < 0){impulse = l;} else {impulse = -c/b+l;}
                circ1->apply_impulse(Z.x(),Z.y(),Z-circ1->Icenter(),-impulse);
                if(!rect1->isBorder) rect1->apply_impulse(Z.x(),Z.y(),Z-circ1->Icenter(),impulse);
            }
        }
    }
    //Прямоугольник и прямоугольник
    if(rect1!= NULL && rect2 != NULL){
        bool key;
        Z = QPointF(0,0);
        int i,j;

        double w1 = rect1->width/2;
        double h1 = rect1->height/2;
        double alpha1 = rect1->Ishape()->rotation()/180*3.1415;
        QPointF R1a = QPointF(rect1->Icenter().x()-w1*cos(alpha1)+h1*sin(alpha1),rect1->Icenter().y()-w1*sin(alpha1)-h1*cos(alpha1));
        QPointF R1b = QPointF(rect1->Icenter().x()+w1*cos(alpha1)+h1*sin(alpha1),rect1->Icenter().y()+w1*sin(alpha1)-h1*cos(alpha1));
        QPointF R1c = QPointF(rect1->Icenter().x()+w1*cos(alpha1)-h1*sin(alpha1),rect1->Icenter().y()+w1*sin(alpha1)+h1*cos(alpha1));
        QPointF R1d = QPointF(rect1->Icenter().x()-w1*cos(alpha1)-h1*sin(alpha1),rect1->Icenter().y()-w1*sin(alpha1)+h1*cos(alpha1));
        QPointF R1[8] = {R1a,R1b,R1b,R1c,R1d,R1c,R1d,R1a};

        double w2 = rect2->width/2;
        double h2 = rect2->height/2;
        double alpha2 = rect2->Ishape()->rotation()/180*3.1415;
        QPointF R2a = QPointF(rect2->Icenter().x()-w2*cos(alpha2)+h2*sin(alpha2),rect2->Icenter().y()-w2*sin(alpha2)-h2*cos(alpha2));
        QPointF R2b = QPointF(rect2->Icenter().x()+w2*cos(alpha2)+h2*sin(alpha2),rect2->Icenter().y()+w2*sin(alpha2)-h2*cos(alpha2));
        QPointF R2c = QPointF(rect2->Icenter().x()+w2*cos(alpha2)-h2*sin(alpha2),rect2->Icenter().y()+w2*sin(alpha2)+h2*cos(alpha2));
        QPointF R2d = QPointF(rect2->Icenter().x()-w2*cos(alpha2)-h2*sin(alpha2),rect2->Icenter().y()-w2*sin(alpha2)+h2*cos(alpha2));
        QPointF R2[8] = {R2a,R2b,R2b,R2c,R2d,R2c,R2d,R2a};

        for(i=0;i<8;i+=2){
            for(j=0;j<8;j+=2){
                key = are_crossing(R1[i], R1[i+1], R2[j], R2[j+1], &Z);
                if(key){
                    double Bx,By;
                    double Ax = R1[i].x()-R1[i+1].x();
                    double Ay = R1[i].y()-R1[i+1].y();
                    if(Ax == 0){
                        By=0;
                        Bx = Z.x()-R1[i].x();
                    }else if(Ay == 0){
                        Bx=0;
                        By = Z.y()-R1[i].y();
                    }else{
                        Bx=1;
                        By=-Ay*Ax/Bx;
                    }
                    QPointF n1 = QPointF(Bx,By);
                    QPointF n2 = -1*n1;
                    double w1 = n1*(Z-rect1->Icenter());
                    double w2 = n2*(Z-rect2->Icenter());
                    double a = n1*rect1->Ivel()+n2*rect2->Ivel()+w1*rect1->Iw()+w2*rect2->Iw();
                    double c = (1+bounce)*a;
                    double b = n1*n1/rect1->Imass()+w1*w1/rect1->Ii()+n2*n2/rect2->Imass()+w2*w2/rect2->Ii();
                    double impulse;
                    double l = (sqrt(n1*n1))*archimed/100000;
                    if(-c/b < 0){impulse = l;} else {impulse = -c/b+l;}
                    if(!rect1->isBorder) rect1->apply_impulse(Z.x(),Z.y(),n1,-impulse);
                    if(!rect2->isBorder) rect2->apply_impulse(Z.x(),Z.y(),n2,impulse);
                }
            }
        }
    }
}


void Widget::frame(){
    list *p1, *p2;
    p1 = root;
    p2 = root;
    while(p1->pNext!=NULL){
        if(p1->nValue1!=NULL) p1->nValue1->gravity();
        //else if(p1->nValue2!=NULL) p1->nValue2->gravity();
        else if(p1->nValue3!=NULL) p1->nValue3->gravity();
        p2=p1->pNext;
        while(p2->pNext!=NULL){
            collision(p1,p2);

            p2=p2->pNext;
        }
        if(p1->nValue1!=NULL) p1->nValue1->move();
        //else if(p1->nValue2!=NULL) p1->nValue2->gravity();
        else if(p1->nValue3!=NULL) p1->nValue3->move();
        p1=p1->pNext;
    }
}



void Widget::spawncirc(QPoint coord){
    int A = rand()%100+30;
    double d = A*scale;

    QRectF Itemrect(coord.x(),coord.y(),d/scale,d/scale);
    QGraphicsItem* item = scene->addEllipse(Itemrect);
    item->setTransformOriginPoint(d/scale/2,d/scale/2);
    QGraphicsRectItem* temp = new QGraphicsRectItem(coord.x()*scale,coord.y()*scale,d,d);
    temp->setTransformOriginPoint(d/2,d/2);
    circle* circ = new circle(temp,coord.x()*scale+d/2,coord.y()*scale+d/2, item,d/2);
    next = next->addToList(NULL, NULL, circ);
}

void Widget::spawntriang(QPoint coord){
    int A = rand()%100+30;
    double a = A*scale;
    QGraphicsRectItem* temp = new QGraphicsRectItem(coord.x(),coord.y(),a,a*sqrt(3)/2);
    QPolygonF triang;
    triang << QPointF(coord.x()+a/2,coord.y()) << QPointF(coord.x(),coord.y()+a*sqrt(3)/2) << QPointF(coord.x()+a,coord.y()+a*sqrt(3)/2);
    QGraphicsItem* item = scene->addPolygon(triang);
    triangle* tri = new triangle(temp,coord.x(),coord.y(), item,a);
    next = next->addToList(NULL, tri, NULL);
}

void Widget::spawnrect(QPointF coord){
    int A = rand()%100+30;
    double a = A*scale;
    int B = rand()%100+30;
    double b = B*scale;
    QRectF Itemrect(coord.x(),coord.y(),A,B);
    QGraphicsItem* item = scene->addRect(Itemrect);
    item->setTransformOriginPoint(A/2,B/2);
    QGraphicsRectItem* temp = new QGraphicsRectItem(coord.x()*scale,coord.y()*scale,a,b);
    temp->setTransformOriginPoint(a/2,b/2);
    rectangle* ret = new rectangle(temp,coord.x()*scale+a/2,coord.y()*scale+b/2, item,false,a,b);
    next = next->addToList(ret);
}

void Widget::placeborders(){
    double P=500,Q=300;
    QRectF lol2(P,Q,50,100);

    QGraphicsItem* lol = scene->addRect(lol2);
    lol->setTransformOriginPoint(P+25,Q+50);
    lol->setRotation(45);

    QGraphicsRectItem* lolI = new QGraphicsRectItem(P*scale,Q*scale,50*scale,100*scale);
    lolI->setTransformOriginPoint((P+25)*scale,(Q+50)*scale);
    lolI->setRotation(45);


    lol->setVisible(true);
    next = next->addToList(new rectangle(lolI,(P+25)*scale,(Q+50)*scale, lol,true,50*scale,100*scale));



    QRectF top(0,0,990,10);
    QRectF left(0,0,10,690);
    QRectF right(980,0,10,690);
    QRectF bottom(0,680,990,10);
    QGraphicsRectItem* Rtop = new QGraphicsRectItem(0*scale,0*scale,990*scale,10*scale);
    QGraphicsRectItem* Rleft = new QGraphicsRectItem(0*scale,0*scale,10*scale,690*scale);
    QGraphicsRectItem* Rright = new QGraphicsRectItem(980*scale,0*scale,10*scale,690*scale);
    QGraphicsRectItem* Rbottom = new QGraphicsRectItem(0*scale,680*scale,990*scale,10*scale);
    QGraphicsItem* itop = scene->addRect(top);
    itop->setVisible(true);
    QGraphicsItem* ileft = scene->addRect(left);
    ileft->setVisible(true);
    QGraphicsItem* iright = scene->addRect(right);
    iright->setVisible(true);
    QGraphicsItem* ibottom = scene->addRect(bottom);
    ibottom->setVisible(true);
    next = next->addToList(new rectangle(Rtop,990/2*scale,5*scale, itop,true,990*scale,10*scale));
    next = next->addToList(new rectangle(Rleft,5*scale,690/2*scale, ileft,true,10*scale,690*scale));
    next = next->addToList(new rectangle(Rright,985*scale,690/2*scale, iright,true,10*scale,690*scale));
    next = next->addToList(new rectangle(Rbottom,990/2*scale,685*scale, ibottom,true,990*scale,10*scale));
}
