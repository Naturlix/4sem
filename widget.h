#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QtWidgets>
#include "list.h"

#define fps 24

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    QPoint mouse;
    QMouseEvent* spawn;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QTimer* timer;
    Ui::Widget *ui;
    void frame();
    void mousePressEvent(QMouseEvent *event);
    void spawnrect(QPointF coord);
    void spawncirc(QPoint coord);
    void spawntriang(QPoint coord);
    list* root;
    list* next;
    void placeborders();
private slots:
    void addtime();

};

#endif // WIDGET_H
