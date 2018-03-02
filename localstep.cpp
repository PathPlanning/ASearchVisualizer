#include "localstep.h"

LocalStep::LocalStep()
{
}

bool LocalStep::setStep(TiXmlElement *elem, QString &error, int stepnum)
{
    if(!GlobalStep::setStep(elem,error,stepnum))
        return false;
    TiXmlElement *localsearch=elem->FirstChildElement("localSearch");
    if(!localsearch)
    {
        error=QString("No localSearch was found at step #%1").arg(QString::number(stepnum));
        return false;
    }

    if(QString(localsearch->Attribute("pathfound")).compare(QString("true"))==0)
        pathfound=true;
    else
        pathfound=false;

    TiXmlElement *startelem=localsearch->FirstChildElement("start");
    if(!startelem)
    {
        error=QString("No start was found at step #%1").arg(QString::number(stepnum));
        return false;
    }
    start=qMakePair(QString(startelem->Attribute("x")).toInt(),QString(startelem->Attribute("y")).toInt());
    TiXmlElement *goalelem=localsearch->FirstChildElement("goal");
    if(!goalelem)
    {
        error=QString("No goal was found at step #%1").arg(QString::number(stepnum));
        return false;
    }
    goal=qMakePair(QString(goalelem->Attribute("x")).toInt(),QString(goalelem->Attribute("y")).toInt());

    TiXmlElement *localopenelem=localsearch->FirstChildElement("localOpen");
    if(!localopenelem)
    {
        error=QString("No localOpen was found at step #%1").arg(QString::number(stepnum));
        return false;
    }
    TiXmlElement *pointelem=localopenelem->FirstChildElement();
    while(pointelem)
    {
        localOpen.append(qMakePair(QString(pointelem->Attribute("x")).toInt(),QString(pointelem->Attribute("y")).toInt()));
        pointelem=pointelem->NextSiblingElement();
    }

    TiXmlElement *localcloseelem=localsearch->FirstChildElement("localClose");
    if(!localcloseelem)
    {
        error=QString("No localClose was found at step #%1").arg(QString::number(stepnum));
        return false;
    }
    pointelem=localcloseelem->FirstChildElement();
    while(pointelem)
    {
        localClose.append(qMakePair(QString(pointelem->Attribute("x")).toInt(),QString(pointelem->Attribute("y")).toInt()));
        pointelem=pointelem->NextSiblingElement();
    }
    return true;
}


QVector<QGraphicsItem*> LocalStep::show(QGraphicsScene* scene, Colors *curcolors, int cellsize) const
{

    QVector<QGraphicsItem*> group=GlobalStep::show(scene,curcolors,cellsize);
    QListIterator<QPair<int,int> > iter(localOpen);
    while(iter.hasNext())
    {
        QPair<int,int> p=iter.next();
        group.push_back(scene->addRect(p.first*cellsize,p.second*cellsize,cellsize,cellsize,QPen(QColor("black")),curcolors->localopen));
    }

    QListIterator<QPair<int,int> > closeiter(localClose);
    while(closeiter.hasNext())
    {
        QPair<int,int> p=closeiter.next();
        group.push_back(scene->addRect(p.first*cellsize,p.second*cellsize,cellsize,cellsize,QPen(QColor("black")),curcolors->localclose));
    }

    group.push_back(scene->addRect(start.first*cellsize,start.second*cellsize,cellsize,cellsize,QPen(QColor("black")),curcolors->localstart));
    group.push_back(scene->addRect(goal.first*cellsize,goal.second*cellsize,cellsize,cellsize,QPen(QColor("black")),curcolors->localgoal));

    return group;

}
