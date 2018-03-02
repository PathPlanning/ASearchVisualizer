#include "mygraphicsview.h"
#include <iostream>
MyGraphicsView::MyGraphicsView(QWidget *parent)
{
}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
        emit wheelrounded(1);
    else
        emit wheelrounded(-1);
}
