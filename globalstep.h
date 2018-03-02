#ifndef GLOBALSTEP_H
#define GLOBALSTEP_H


#include <QList>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include <qmath.h>
#include <math.h>

#include "tinyxml/tinyxml.h"
#include "point.h"
#include "colors.h"


class GlobalStep
{
public:
    GlobalStep();
    bool setStep(TiXmlElement *elem, QString &error, int stepnum);
    QVector<QGraphicsItem*> show(QGraphicsScene* scene, Colors *curcolors, int cellsize) const;

    QVector<QGraphicsItem*> showArrows(QGraphicsScene* scene, Colors *curcolors, int cellsize) const;
    //QVector<QGraphicsItem*> showLabels(QGraphicsScene* scene, Colors *curcolors, int cellsize) const;
    QVector<QGraphicsItem *> drawArrowsForPoint(QGraphicsScene* scene, Colors *curcolors, int cellsize, int x, int y) const;
    QVector<QGraphicsItem*> drawPathForPoint(QGraphicsScene* scene, Colors *curcolors, int cellsize, int x, int y) const;

    bool findPoint(int x, int y, Point &p) const;

protected:
    QList<Point> open;
    QList<Point> close;


    QVector<QGraphicsItem*> drawArrowsForPoint(const Point p, QGraphicsScene* scene, QColor color, int cellsize) const;

    QList<Point> findPointInList(int x, int y, bool lookopen, bool lookparents) const;

};

#endif // GLOBALSTEP_H
