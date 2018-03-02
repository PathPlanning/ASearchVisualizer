#ifndef ISTEP_H
#define ISTEP_H

#include <QGraphicsScene>
#include "colors.h"

class iStep
{
public:
    int number;
    int mode;
    virtual void show(QGraphicsScene* scene, Colors *curcolors, int cellsize)=0;

};


#endif // ISTEP_H
