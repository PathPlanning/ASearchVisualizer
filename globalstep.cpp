#include "globalstep.h"

GlobalStep::GlobalStep()
{

}

bool GlobalStep::setStep(TiXmlElement *elem, QString &error, int stepnum)
{
    open.clear();
    close.clear();
    TiXmlElement *openelem=elem->FirstChildElement("open");
    if(!openelem)
    {
        error=QString("No open list found at step #%1").arg(QString::number(stepnum));
        return false;
    }
    TiXmlElement *point=openelem->FirstChildElement();
    while(point)
    {
        open.append(Point(point));
        point=point->NextSiblingElement();
    }

    TiXmlElement *closeelem=elem->FirstChildElement("close");
    if(!closeelem)
    {
        error=QString("No close list found at step #%1").arg(QString::number(stepnum));
        return false;
    }
    point=closeelem->FirstChildElement();
    while(point)
    {
        close.append(Point(point));
        point=point->NextSiblingElement();
    }

    return true;
}

QVector<QGraphicsItem*> GlobalStep::show(QGraphicsScene* scene, Colors *curcolors, int cellsize) const
{
    QVector<QGraphicsItem*> group;
    QListIterator<Point> iter(open);
    iter=QListIterator<Point>(close);
    while(iter.hasNext())
    {
        Point p=iter.next();
        group.push_back(scene->addRect(p.x*cellsize,p.y*cellsize,cellsize,cellsize,QPen(QColor("black")),curcolors->globalclose));
        if(cellsize>49)
        {
            QGraphicsTextItem * io = new QGraphicsTextItem();
            group.push_back(io);
            io->setPos(p.x*cellsize,p.y*cellsize);
            io->setPlainText(QString::number(p.f));
            scene->addItem(io);
            io = new QGraphicsTextItem;
            group.push_back(io);
            io->setPos(p.x*cellsize,(p.y+1)*cellsize-20);
            io->setPlainText(QString::number(p.g));
            scene->addItem(io);
        }
        if(cellsize>30)
        if((p.parent_x>=0)&&(p.parent_y>=0))
        {

                    qreal vx=p.x*cellsize-p.parent_x*cellsize;
                    qreal vy=p.y*cellsize-p.parent_y*cellsize;
                    qreal fpx=vx*qCos(M_PI/6)-vy*qSin(M_PI/6);
                    qreal fpy=vx*qSin(M_PI/6)+vy*qCos(M_PI/6);
                    qreal length=qSqrt(fpx*fpx+fpy*fpy);
                    qreal spx=vx*qCos(M_PI/6)+vy*qSin(M_PI/6);
                    qreal spy=-vx*qSin(M_PI/6)+vy*qCos(M_PI/6);

                    fpx*=(cellsize/6/length);
                    fpy*=(cellsize/6/length);
                    spx*=(cellsize/6/length);
                    spy*=(cellsize/6/length);
                    int w=2;
                    if(cellsize>40)
                        w=cellsize/20;
                    group.push_back(scene->addLine(p.x*cellsize+cellsize/2,p.y*cellsize+cellsize/2,fpx+p.x*cellsize+cellsize/2,fpy+p.y*cellsize+cellsize/2,QPen(QColor("black"),w)));
                    group.push_back(scene->addLine(p.x*cellsize+cellsize/2,p.y*cellsize+cellsize/2,spx+p.x*cellsize+cellsize/2,spy+p.y*cellsize+cellsize/2,QPen(QColor("black"),w)));
         }
    }
    iter=QListIterator<Point>(open);
    while(iter.hasNext())
    {
        Point p=iter.next();
        group.push_back(scene->addRect(p.x*cellsize,p.y*cellsize,cellsize,cellsize,QPen(QColor("black")),curcolors->globalopen));
        if(cellsize>49)
        {
            QGraphicsTextItem * io = new QGraphicsTextItem();
            group.push_back(io);
            io->setPos(p.x*cellsize,p.y*cellsize);
            io->setPlainText(QString::number(p.f));
            scene->addItem(io);
            io = new QGraphicsTextItem;
            group.push_back(io);
            io->setPos(p.x*cellsize,(p.y+1)*cellsize-20);
            io->setPlainText(QString::number(p.g));
            scene->addItem(io);
        }
        if(cellsize>30)
        if((p.parent_x>=0)&&(p.parent_y>=0))
        {
            qreal vx=p.x*cellsize-p.parent_x*cellsize;
            qreal vy=p.y*cellsize-p.parent_y*cellsize;
            qreal fpx=vx*qCos(M_PI/6)-vy*qSin(M_PI/6);
            qreal fpy=vx*qSin(M_PI/6)+vy*qCos(M_PI/6);
            qreal length=qSqrt(fpx*fpx+fpy*fpy);
            qreal spx=vx*qCos(M_PI/6)+vy*qSin(M_PI/6);
            qreal spy=-vx*qSin(M_PI/6)+vy*qCos(M_PI/6);

            fpx*=(cellsize/6/length);
            fpy*=(cellsize/6/length);
            spx*=(cellsize/6/length);
            spy*=(cellsize/6/length);
            int w=2;
            if(cellsize>40)
                w=cellsize/20;
            group.push_back(scene->addLine(p.x*cellsize+cellsize/2,p.y*cellsize+cellsize/2,fpx+p.x*cellsize+cellsize/2,fpy+p.y*cellsize+cellsize/2,QPen(QColor("black"),w)));
            group.push_back(scene->addLine(p.x*cellsize+cellsize/2,p.y*cellsize+cellsize/2,spx+p.x*cellsize+cellsize/2,spy+p.y*cellsize+cellsize/2,QPen(QColor("black"),w)));

        }
    }
    iter=QListIterator<Point>(open);
    Point p=iter.next();
    group.push_back(scene->addRect(p.x*cellsize,p.y*cellsize,cellsize,cellsize,QPen(QColor("black"),3),curcolors->globalopen));
    if(cellsize>49)
    {
        QGraphicsTextItem * io = new QGraphicsTextItem();
        group.push_back(io);
        io->setPos(p.x*cellsize,p.y*cellsize);
        io->setPlainText(QString::number(p.f));
        scene->addItem(io);
        io = new QGraphicsTextItem;
        group.push_back(io);
        io->setPos(p.x*cellsize,(p.y+1)*cellsize-20);
        io->setPlainText(QString::number(p.g));
        scene->addItem(io);
    }
    if(cellsize>30)
    if((p.parent_x>=0)&&(p.parent_y>=0))
    {
        qreal vx=p.x*cellsize-p.parent_x*cellsize;
        qreal vy=p.y*cellsize-p.parent_y*cellsize;
        qreal fpx=vx*qCos(M_PI/6)-vy*qSin(M_PI/6);
        qreal fpy=vx*qSin(M_PI/6)+vy*qCos(M_PI/6);
        qreal length=qSqrt(fpx*fpx+fpy*fpy);
        qreal spx=vx*qCos(M_PI/6)+vy*qSin(M_PI/6);
        qreal spy=-vx*qSin(M_PI/6)+vy*qCos(M_PI/6);

        fpx*=(cellsize/6/length);
        fpy*=(cellsize/6/length);
        spx*=(cellsize/6/length);
        spy*=(cellsize/6/length);
        int w=2;
        if(cellsize>40)
            w=cellsize/20;
        group.push_back(scene->addLine(p.x*cellsize+cellsize/2,p.y*cellsize+cellsize/2,fpx+p.x*cellsize+cellsize/2,fpy+p.y*cellsize+cellsize/2,QPen(QColor("black"),w)));
        group.push_back(scene->addLine(p.x*cellsize+cellsize/2,p.y*cellsize+cellsize/2,spx+p.x*cellsize+cellsize/2,spy+p.y*cellsize+cellsize/2,QPen(QColor("black"),w)));

    }


    return group;
}

QVector<QGraphicsItem*> GlobalStep::showArrows(QGraphicsScene* scene, Colors *curcolors, int cellsize) const
{
    QVector<QGraphicsItem*> group;
    QColor color;
    QListIterator<Point> iter(open);
    while(iter.hasNext())
    {
        Point p=iter.next();
        color=curcolors->freearrow;
        group+=drawArrowsForPoint(p,scene,color,cellsize);
    }

    QListIterator<Point> closeiter(close);
    while(closeiter.hasNext())
    {
        Point p=closeiter.next();
        color=curcolors->freearrow;
        group+=drawArrowsForPoint(p,scene,color,cellsize);
    }
    return group;
}


QVector<QGraphicsItem*>  GlobalStep::drawArrowsForPoint(Point p, QGraphicsScene* scene, QColor color, int cellsize) const
{
    QVector<QGraphicsItem*> group;
    if((p.parent_x>=0)&&(p.parent_y>=0))
    {
        group.push_back(scene->addLine(p.x*cellsize+cellsize/2,p.y*cellsize+cellsize/2,p.parent_x*cellsize+cellsize/2,p.parent_y*cellsize+cellsize/2,QPen(color,cellsize/5)));

        qreal vx=p.x*cellsize-p.parent_x*cellsize;
        qreal vy=p.y*cellsize-p.parent_y*cellsize;
        qreal fpx=vx*qCos(M_PI/6)-vy*qSin(M_PI/6);
        qreal fpy=vx*qSin(M_PI/6)+vy*qCos(M_PI/6);
        qreal length=qSqrt(fpx*fpx+fpy*fpy);
        qreal spx=vx*qCos(M_PI/6)+vy*qSin(M_PI/6);
        qreal spy=-vx*qSin(M_PI/6)+vy*qCos(M_PI/6);

        fpx*=(cellsize/5/length);
        fpy*=(cellsize/5/length);
        spx*=(cellsize/5/length);
        spy*=(cellsize/5/length);

        group.push_back(scene->addLine(p.parent_x*cellsize+cellsize/2,p.parent_y*cellsize+cellsize/2,fpx+p.parent_x*cellsize+cellsize/2,fpy+p.parent_y*cellsize+cellsize/2,QPen(color,cellsize/5)));
        group.push_back(scene->addLine(p.parent_x*cellsize+cellsize/2,p.parent_y*cellsize+cellsize/2,spx+p.parent_x*cellsize+cellsize/2,spy+p.parent_y*cellsize+cellsize/2,QPen(color,cellsize/5)));
    }

    return group;
}


QVector<QGraphicsItem*> GlobalStep::drawArrowsForPoint(QGraphicsScene* scene, Colors *curcolors, int cellsize, int x, int y) const
{
    QVector<QGraphicsItem*> group;
    QColor color;
    QListIterator<Point> iter(open);
    while(iter.hasNext())
    {
        Point p=iter.next();
        if((p.x==x)&&(p.y==y))
        {
            color=curcolors->freearrow;
            group+=drawArrowsForPoint(p,scene,color,cellsize);
        }
        if((p.parent_x==x)&&(p.parent_y==y))
        {
            color=curcolors->undefarrow;
            group+=drawArrowsForPoint(p,scene,color,cellsize);
        }
    }

    QListIterator<Point> closeiter(close);
    while(closeiter.hasNext())
    {
        Point p=closeiter.next();
        if((p.x==x)&&(p.y==y))
        {
            color=curcolors->freearrow;
            group+=drawArrowsForPoint(p,scene,color,cellsize);
        }
        if((p.parent_x==x)&&(p.parent_y==y))
        {
            color=curcolors->undefarrow;
            group+=drawArrowsForPoint(p,scene,color,cellsize);
        }
    }

    return group;
}

bool GlobalStep::findPoint(int x, int y, Point &p) const
{
    QListIterator<Point> iter(open);
    while(iter.hasNext())
    {
        Point curpoint=iter.next();
        if((curpoint.x==x)&&(curpoint.y==y))
        {
            p=curpoint;
            return true;
        }
    }

    QListIterator<Point> closeiter(close);
    while(closeiter.hasNext())
    {
        Point curpoint=closeiter.next();
        if((curpoint.x==x)&&(curpoint.y==y))
        {
            p=curpoint;
            return true;
        }
    }

    return false;

}


QVector<QGraphicsItem*> GlobalStep::drawPathForPoint(QGraphicsScene *scene, Colors *curcolors, int cellsize, int x, int y) const
{
    QVector<QGraphicsItem*> group;
    QList<Point> dots=this->findPointInList(x,y,true,false);
    while(!dots.empty())
    {
        Point p=dots.first();
        dots.pop_front();
        QList<Point> parents=this->findPointInList(p.parent_x,p.parent_y,false,false);
        group += drawArrowsForPoint(p,scene,curcolors->pathcolor,cellsize);
        for(Point pp : parents)
            dots.push_back(pp);
    }

    return group;
}

QList<Point> GlobalStep::findPointInList(int x, int y, bool lookopen, bool lookparents) const
{
    QList<Point> result;
    if(lookopen)
    {
        QListIterator<Point> iter(open);
        while(iter.hasNext())
        {
            Point p=iter.next();

            if(((p.x==x)&&(p.y==y))||(lookparents&&(p.parent_x==x)&&(p.parent_y==y)))
            {
                result.push_back(p);
            }

        }
    }
    QListIterator<Point> closeiter(close);
    while(closeiter.hasNext())
    {
        Point p=closeiter.next();
        if(((p.x==x)&&(p.y==y))||(lookparents&&(p.parent_x==x)&&(p.parent_y==y)))
        {
            result.push_back(p);
        }
    }
    
    return result;
}
