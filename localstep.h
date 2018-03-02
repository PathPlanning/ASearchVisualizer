#ifndef LOCALSTEP_H
#define LOCALSTEP_H

#include <QGraphicsScene>
#include <iostream>
#include <QString>
#include <QPair>
#include <QList>

#include <QGraphicsItem>

#include "tinyxml/tinyxml.h"
#include "colors.h"
#include "globalstep.h"

class LocalStep: public GlobalStep
{

    public:
        LocalStep();
        bool setStep(TiXmlElement *elem, QString &error, int stepnum);
        QVector<QGraphicsItem *> show(QGraphicsScene* scene, Colors *curcolors, int cellsize) const;



    private:
        bool pathfound;
        QPair<int,int> start;
        QPair<int,int> goal;
        QList<QPair<int,int> > localOpen;
        QList<QPair<int,int> > localClose;
        int number;
        int mode;


};

#endif // LOCALSTEP_H
