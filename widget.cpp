#include "widget.h"
#include "ui_widget.h"


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
    if(i == 1) spawnrect(e->localPos()/2);
    if(i == 2) spawncirc(e->pos()/2);
    if(i == 3) spawntriang(e->pos()/2);
}

void Widget::frame(){
    list* p;
    p = root;
    while( p != NULL && p->pNext != NULL){
        if(p->nValue1 != NULL)
            p->nValue1->gravity();
        if(p->nValue2 != NULL)
            p->nValue2->gravity();
        if(p->nValue3 != NULL)
            p->nValue3->gravity();
        p = p->pNext;
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
    int r = rand()%100+30;
    QRectF* temp = new QRectF(coord.x(),coord.y(),r,r);
    QGraphicsItem* item = scene->addEllipse(*temp);
    circle* circ = new circle(*temp,coord.x(),coord.y(), item);
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
