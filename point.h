#ifndef POINT_H
#define POINT_H

#include <QString>
#include <tinyxml/tinyxml.h>

struct Point{
    int x;
    int y;
    double f;
    double g;
    int k;
    QString pathfound;
    int pathfoundint;
    QString label;
    bool labelnormal;
    int parent_x;
    int parent_y;

    Point():x(-1),y(-1){}


    Point(TiXmlElement *p)
    {
        if(p->Attribute("x"))
            x=QString(p->Attribute("x")).toInt();
        if(p->Attribute("y"))
            y=QString(p->Attribute("y")).toInt();
        if(p->Attribute("F"))
            f=QString(p->Attribute("F")).toDouble();
        if(p->Attribute("g"))
            g=QString(p->Attribute("g")).toDouble();
        if(p->Attribute("pathFound"))
        pathfound=QString(p->Attribute("pathFound"));
        if(pathfound.compare("noAttempt")==0)
            pathfoundint=0;
        else if(pathfound.compare("true")==0)
            pathfoundint=1;
        else
            pathfoundint=-1;
        label=QString(p->Attribute("label")?p->Attribute("label"):"");

        if(p->Attribute("k"))
            k=QString(p->Attribute("k")).toInt();
        else
            k=-1;
        labelnormal=(k!=1);
        if(p->Attribute("parent_x"))
            parent_x=QString(p->Attribute("parent_x")).toInt();
        else
            parent_x=-1;

        if(p->Attribute("parent_y"))
            parent_y=QString(p->Attribute("parent_y")).toInt();
        else
            parent_y=-1;
    }

    Point(int x,int y, double f, double g, int k, QString pathfound, QString label=QString(),int parent_x=-1, int parent_y=-1):
        x(x),y(y),f(f),g(g),k(k),pathfound(pathfound),label(label),parent_x(parent_x),parent_y(parent_y){}

};

#endif // POINT_H
