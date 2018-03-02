#ifndef MAP_H
#define MAP_H

#include "tinyxml/tinyxml.h"
#include <QString>
#include <QList>
#include <QPair>
#include <QStringList>
#include <QGraphicsScene>
#include "colors.h"
class Map
{
public:    
    Map();

    bool parseMap(TiXmlElement* elem, QString &error);
    QGraphicsScene* drawclearmap(Colors *curcolors);
    void setcellsize(int size);
    int getcellsize();
    int getmapwidth();
    int getmapheight();

private:
    int cellsize;
    int width;
    int height;
    int startx;
    int starty;
    int finishx;
    int finishy;
    QList<QPair<int,int> > obstacles;
};

#endif // MAP_H
