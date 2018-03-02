#include "map.h"

Map::Map()
{
    width=-1;
    height=-1;
    startx=-1;
    starty=-1;
    finishx=-1;
    finishy=-1;
    obstacles.clear();
}

bool Map::parseMap(TiXmlElement *elem, QString& error)
{
    TiXmlElement *subelem=elem->FirstChildElement("width");
    if(!subelem)
    {
        error=QString::fromUtf8("Width tag not found");
        return false;
    }
    width=QString(subelem->GetText()).toInt();

    subelem=elem->FirstChildElement("height");
    if(!subelem)
    {
        error=QString::fromUtf8("Height tag not found");
        return false;
    }
    height=QString(subelem->GetText()).toInt();

    subelem=elem->FirstChildElement("startx");
    if(!subelem)
    {
        error=QString::fromUtf8("Startx tag not found");
        return false;
    }
    startx=QString(subelem->GetText()).toInt();

    subelem=elem->FirstChildElement("starty");
    if(!subelem)
    {
        error=QString::fromUtf8("Starty tag not found");
        return false;
    }
    starty=QString(subelem->GetText()).toInt();

    subelem=elem->FirstChildElement("finishx");
    if(!subelem)
    {
        error=QString::fromUtf8("Finishx tag not found");
        return false;
    }
    finishx=QString(subelem->GetText()).toInt();

    subelem=elem->FirstChildElement("finishy");
    if(!subelem)
    {
        error=QString::fromUtf8("Finishy tag not found");
        return false;
    }
    finishy=QString(subelem->GetText()).toInt();


    subelem=elem->FirstChildElement("grid");
    if(!subelem)
    {
        error=QString::fromUtf8("Grid tag not found");
        return false;
    }
    TiXmlElement *row=subelem->FirstChildElement();
    if(!row)
    {
        error=QString::fromUtf8("Incorrect grid rows");
        return false;
    }
    int rownumber=0;
    while(row)
    {

        QStringList rowelements=QString(row->GetText()).split(" ");
        if(rowelements.count()!=width)
        {
            error=QString::fromUtf8("Length of row #%1 is incorrect").arg(QString::number(rownumber));
            return false;
        }
        if(rowelements.contains(QString("1")))
        {
            int colnumber=0;
            for(QStringList::iterator iter=rowelements.begin();iter!=rowelements.end();iter++,colnumber++)
                if(iter->compare(QString("1"))==0)
                    obstacles.push_back(qMakePair(rownumber, colnumber));
        }
        rownumber++;
        row=row->NextSiblingElement();
    }

    if(rownumber!=height)
    {
        error=QString::fromUtf8("Number of rows and height are not equal");
        return false;
    }

    return true;
}



QGraphicsScene* Map::drawclearmap(Colors *curcolors)
{
    QGraphicsScene *myscene=new QGraphicsScene();
    for(int i=0;i<=width;i++)
        myscene->addLine(i*cellsize, 0, i*cellsize, height*cellsize);
    for(int i=0;i<=height;i++)
        myscene->addLine(0, i*cellsize, width*cellsize, i*cellsize);
    for(int i=0;i<obstacles.size();i++)
    {
        myscene->addRect(obstacles[i].second*cellsize, obstacles[i].first*cellsize, cellsize, cellsize, QPen(QColor("black")), curcolors->obst);
    }
    myscene->addRect(startx*cellsize, starty*cellsize, cellsize, cellsize, QPen(QColor("black")), curcolors->start);
    myscene->addRect(finishx*cellsize, finishy*cellsize, cellsize, cellsize, QPen(QColor("black")), curcolors->goal);
    return myscene;

}


void Map::setcellsize(int size)
{
    cellsize=size;
}


int Map::getcellsize()
{
    return cellsize;
}

int Map::getmapwidth()
{
    return cellsize*width;
}

int Map::getmapheight()
{
    return cellsize*height;
}
