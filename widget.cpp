#include "widget.h"
#include "ui_widget.h"
#include "geometry.cpp"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene,this);
    view->setFixedSize(1000,700);
    view->setSceneRect(0,0,990,690);
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
    int i = rand()%3+1;
    if(i == 1) spawnrect(e->localPos());
    if(i == 2) spawncirc(e->pos());
    if(i == 3) spawntriang(e->pos());
}

void Widget::collision(list* p1, list* p2){
    rectangle* rect1 = NULL;
    rectangle* rect2 = NULL;
    triangle* triang1 = NULL;
    triangle* triang2 = NULL;
    circle* circ1 = NULL;
    circle* circ2 = NULL;

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
    /*if(circ1!= NULL && circ2 != NULL){
        QPointF check;
        check = circ1->Icenter()-circ2->Icenter();
        if(check.manhattanLength() < circ1->Irad()+circ2->Irad() )
    }*/
    // Прямоугольник и круг
    if(rect1!= NULL && circ1 != NULL){
        QPointF Z=QPointF(0,0);
        if( CircleIntersects(circ1->Icenter(), circ1->Irad(), rect1->Ishape().topLeft(),rect1->Ishape().topRight(), &Z)){
            QPointF R1 = QPointF(Z.x()-circ1->Icenter().x(),Z.y()-circ1->Icenter().y());
            QPointF R2 = QPointF(Z.x()-rect1->Icenter().x(),Z.y()-rect1->Icenter().y());
            double vab = R1.x() * (circ1->Ivel().x() - circ1->Iw() * R1.y() - rect1->Ivel().x() + rect1->Iw() * R2.y()) + R1.y() * (circ1->Ivel().y() + circ1->Iw() * R1.x() - rect1->Ivel().y() - rect1->Iw() * R2.x());
            double Z1 = (R1.y() * R1.x() - R1.x() * R1.y()) / circ1->Ii();
            double Z2 = (R1.y() * R2.x() - R1.x() * R2.y()) / rect1->Ii();
            double J = R1.x() *  (R1.x() / circ1->Imass() - R1.y() * Z1 + R1.x() / rect1->Imass() + R2.y() * Z2)
            +   R1.y() * (R1.y() / circ1->Imass() + R1.x() * Z1 / circ1->Ii()
            +   R1.y() / rect1->Imass() - R2.x() * Z2 / rect1->Ii());
            double impulse = ( 10 - (1 + 0.5) * vab ) / J;
            circ1->apply_impulse(Z.x(),Z.y(),Z-circ1->Icenter(),-impulse/1000);}
        /*if(CircleIntersects(circ1->Icenter(), circ1->Irad(), rect1->Ishape().topRight(),rect1->Ishape().bottomRight(), &Z)){
            circ1->apply_impulse(Z.x(),Z.y(),Z-circ1->Icenter(),-0.01);}
        if(CircleIntersects(circ1->Icenter(), circ1->Irad(), rect1->Ishape().bottomRight(),rect1->Ishape().bottomLeft(), &Z)){
            circ1->apply_impulse(Z.x(),Z.y(),Z-circ1->Icenter(),-0.01);}
        if(CircleIntersects(circ1->Icenter(), circ1->Irad(), rect1->Ishape().topLeft(),rect1->Ishape().bottomLeft(),&Z)){
            circ1->apply_impulse(Z.x(),Z.y(),Z-circ1->Icenter(),-0.01);}*/
    }
    //Треугольник и круг
    //Прямоугольник и треугольник
    //Прямоугольник и прямоугольник
    //Треугольник и треугольник
}


void Widget::frame(){
    list *p1, *p2;
    p1 = root;
    p2 = root;
    while(p1->pNext!=NULL){
        /*if(p1->nValue1!=NULL) p1->nValue1->gravity();
        else if(p1->nValue2!=NULL) p1->nValue2->gravity();
        else */if(p1->nValue3!=NULL) p1->nValue3->gravity();
        p2=p1->pNext;
        while(p2->pNext!=NULL){
            collision(p1,p2);

            p2=p2->pNext;
        }
        /*if(p1->nValue1!=NULL) p1->nValue1->gravity();
        else if(p1->nValue2!=NULL) p1->nValue2->gravity();
        else */if(p1->nValue3!=NULL) p1->nValue3->move();
        p1=p1->pNext;
    }
}

void Widget::spawnrect(QPointF coord){
    int a = rand()%100+30;
    int b = rand()%100+30;
    QRectF* temp = new QRectF(coord.x(),coord.y(),a,b);
    QGraphicsItem* item = scene->addRect(*temp);
    rectangle* ret = new rectangle(*temp,coord.x(),coord.y(), item,false);
    next = next->addToList(ret);
}

void Widget::spawncirc(QPoint coord){
    int d = rand()%100+30;
    QRectF* temp = new QRectF(coord.x(),coord.y(),d,d);
    QGraphicsItem* item = scene->addEllipse(*temp);
    item->setTransformOriginPoint(d/2,d/2);
    circle* circ = new circle(*temp,coord.x()+d/2,coord.y()+d/2, item);
    next = next->addToList(NULL, NULL, circ);
}

void Widget::spawntriang(QPoint coord){
    int a = rand()%100+30;
    QRectF* temp = new QRectF(coord.x(),coord.y(),a,a*sqrt(3)/2);
    QPolygonF triang;
    triang << QPointF(coord.x()+a/2,coord.y()) << QPointF(coord.x(),coord.y()+a*sqrt(3)/2) << QPointF(coord.x()+a,coord.y()+a*sqrt(3)/2);
    QGraphicsItem* item = scene->addPolygon(triang);
    triangle* tri = new triangle(*temp,coord.x(),coord.y(), item);
    next = next->addToList(NULL, tri, NULL);
}

void Widget::placeborders(){
    QRectF* top = new QRectF(0,0,990,10);
    QRectF* left = new QRectF(0,0,10,690);
    QRectF* right = new QRectF(980,0,10,690);
    QRectF* bottom = new QRectF(0,680,990,10);
    QGraphicsItem* itop = scene->addRect(*top);
    itop->setVisible(true);
    QGraphicsItem* ileft = scene->addRect(*left);
    ileft->setVisible(true);
    QGraphicsItem* iright = scene->addRect(*right);
    iright->setVisible(true);
    QGraphicsItem* ibottom = scene->addRect(*bottom);
    ibottom->setVisible(true);
    next = next->addToList(new rectangle(*top,0,0, itop,true));
    next = next->addToList(new rectangle(*left,0,0, ileft,true));
    next = next->addToList(new rectangle(*right,980,0, iright,true));
    next = next->addToList(new rectangle(*bottom,0,680, ibottom,true));
}
