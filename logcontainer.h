#ifndef LOGCONTAINER_H
#define LOGCONTAINER_H

#include "tinyxml/tinyxml.h"
#include "globalstep.h"
#include "localstep.h"
#include "iStep.h"
#include <QList>
#include <QPair>
#include <QString>
#include "point.h"
class LogContainer
{
public:    
    LogContainer();

    bool parseLog(TiXmlElement *elem, QString& error);
    int numofsteps();
    QVector<QGraphicsItem*> showGlobalStep(QGraphicsScene *scene, int stepnum, Colors *curcolors, int cellsize, bool showarrows, bool showpath);
    QVector<QGraphicsItem*> showArrowsOfPoint(QGraphicsScene *scene, int stepnum, Colors *curcolors, int cellsize, int x, int y);
    bool findPoint(int stepnum, int x, int y, Point &point);
    QVector<QGraphicsItem*> showPath(QGraphicsScene *scene,int cellsize, Colors *curcolors);

    QVector<QGraphicsItem*> showPathToPoint(QGraphicsScene *scene, int stepnum, Colors *curcolors, int cellsize, int x, int y);


private:
    QList<GlobalStep*> steps;
    QList<QPair<int,int> > path;

};

#endif // LOGCONTAINER_H
