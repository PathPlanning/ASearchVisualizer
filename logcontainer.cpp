#include "logcontainer.h"

LogContainer::LogContainer()
{

}

bool LogContainer::parseLog(TiXmlElement *elem, QString& error)
{
    path.clear();
    steps.clear();
    TiXmlElement *pathelem=elem->FirstChildElement("lplevel");
    if(pathelem)
    {

        TiXmlElement *point=pathelem->FirstChildElement();
        if(point)
            while(point)
            {
                if((point->Attribute("x"))&&(point->Attribute("y")))
                    path.append(qMakePair(QString(point->Attribute("x")).toInt(),QString(point->Attribute("y")).toInt()));
                point=point->NextSiblingElement();
            }
    }

    TiXmlElement *lowlevelelem=elem->FirstChildElement("lowlevel");
    if(!lowlevelelem)
    {
        error=QString("No lowlevel element was found");
        return false;
    }
    TiXmlElement *stepelem=lowlevelelem->FirstChildElement();
    if(!stepelem)
    {
        error=QString("Low level log is empty");
        return false;
    }
    int stepcount=0;
    while(stepelem)
    {        
        GlobalStep *gl=new GlobalStep();
        if(!gl->setStep(stepelem,error,stepcount))
            return false;
        steps.append(gl);
        stepelem=stepelem->NextSiblingElement();
        stepcount++;
    }
    return true;
}


int LogContainer::numofsteps()
{
    return steps.count();
}


QVector<QGraphicsItem*> LogContainer::showGlobalStep(QGraphicsScene *scene, int stepnum, Colors *curcolors, int cellsize,bool showarrows, bool showpath)
{
    QVector<QGraphicsItem*> group=steps.at(stepnum-1)->show(scene,curcolors,cellsize);
    if(showarrows)
        group+=steps.at(stepnum-1)->showArrows(scene,curcolors,cellsize);
    if(stepnum==this->numofsteps() && showpath)
        group+=this->showPath(scene,cellsize,curcolors);
    return group;
}

QVector<QGraphicsItem*> LogContainer::showArrowsOfPoint(QGraphicsScene *scene, int stepnum, Colors *curcolors, int cellsize, int x, int y)
{
    return steps.at(stepnum-1)->drawArrowsForPoint(scene,curcolors,cellsize,x,y);
}

bool LogContainer::findPoint(int stepnum, int x, int y, Point& point)
{
    return steps.at(stepnum-1)->findPoint(x,y,point);
}


QVector<QGraphicsItem*> LogContainer::showPath(QGraphicsScene *scene,int cellsize, Colors *curcolors)
{
    QVector<QGraphicsItem*> group;
    for(QPair<int,int> p : path)
    {
        group.push_back(scene->addRect(p.first*cellsize,p.second*cellsize,cellsize,cellsize,QPen(curcolors->goalpath),curcolors->goalpath));
    }

    return group;
}


QVector<QGraphicsItem*> LogContainer::showPathToPoint(QGraphicsScene *scene, int stepnum, Colors *curcolors, int cellsize, int x, int y)
{
    return steps.at(stepnum-1)->drawPathForPoint(scene,curcolors,cellsize,x,y);
}
