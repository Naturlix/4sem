#include "list.h"

list::list()
{
    nValue1=NULL;
    nValue2=NULL;
    nValue3=NULL;
    pNext=NULL;
}

list* list::addToList(rectangle* nValue1,triangle* nValue2,circle* nValue3)
{
    list *pList,*pNew;
    pList=this;
    pNew=new list();
    pNew->nValue1=nValue1;
    pNew->nValue2=nValue2;
    pNew->nValue3=nValue3;
    pList->pNext=pNew;
    return pNew;
}
