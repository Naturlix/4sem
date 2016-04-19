#ifndef LIST_H
#define LIST_H
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"

class list
{
public:
    list();
    ~list();
    rectangle* nValue1;
    triangle* nValue2;
    circle* nValue3;
    list *pNext;
    list* addToList(rectangle* nValue1 = NULL,triangle* nValue2 = NULL,circle* nValue3 = NULL);

};

#endif // LIST_H
