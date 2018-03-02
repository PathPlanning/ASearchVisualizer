#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    window=0;

    pointerx=-1;
    pointery=-1;
    maploaded=false;
    curcolors=new Colors();
    QSettings settings("ISA", "ASearchVisualizer");
    settings.beginGroup("Colors");
    curcolors->obst=settings.value("obst",QColor("black")).value<QColor>();
    curcolors->start=settings.value("start",QColor("green")).value<QColor>();
    curcolors->goal=settings.value("goal",QColor("blue")).value<QColor>();
    curcolors->goalpath=settings.value("goalpath",QColor(245,170,255)).value<QColor>();
    curcolors->globalclose=settings.value("globalclose",QColor(160,240,160)).value<QColor>();
    curcolors->globalopen=settings.value("globalopen",QColor(150,150,225)).value<QColor>();
    curcolors->undefarrow=settings.value("undefarrow",QColor(150,150,150)).value<QColor>();
    curcolors->freearrow=settings.value("freearrow",QColor("green")).value<QColor>();
    curcolors->pathcolor=settings.value("pathcolor", QColor("yellow")).value<QColor>();

    settings.endGroup();


    ui->setupUi(this);    

    colorwindow=new color_window();
    colorwindow->setcolors(curcolors);

    ui->lError->setVisible(false);
    ui->closeError->setVisible(false);
    connect(ui->mapField,SIGNAL(mouseMoveEvent(QMouseEvent *)),this,SLOT(on_mapField_mouseMoveEvent(QMouseEvent *)));

    connect(ui->mapField, SIGNAL(wheelrounded(int)), this, SLOT(on_wheel_rounded(int)));

    connect(ui->mapField,SIGNAL(mousePressEvent(QMouseEvent*)),this,SLOT(on_mapField_mousePressEvent(QMouseEvent *)));



}

MainWindow::~MainWindow()
{
    QSettings settings("ISA", "ASearchVisualizer");
    settings.beginGroup("Colors");
    settings.setValue("obst",curcolors->obst);
    settings.setValue("start",curcolors->start);
    settings.setValue("goal",curcolors->goal);
    settings.setValue("goalpath",curcolors->goalpath);
    settings.setValue("globalclose",curcolors->globalclose);
    settings.setValue("globalopen",curcolors->globalopen);
    settings.setValue("undefarrow",curcolors->undefarrow);
    settings.setValue("freearrow",curcolors->freearrow);
    settings.endGroup();

    if(colorwindow)
        delete colorwindow;
    if(window)
        delete window;
    if(ui->mapField->scene())
        delete ui->mapField->scene();
    delete curcolors;
    delete ui;
}

void MainWindow::on_openfilemenuaction_triggered()
{
    ui->lError->setVisible(false);
    ui->closeError->setVisible(false);
    QString error;
    QString filename=QFileDialog::getOpenFileName(0,QString(),QString(),tr("XML(*.xml);;"));
    this->setWindowTitle(filename);
    maploaded=openfile(filename,error);

    if(maploaded)
    {

        //if(ui->mapField->scene())
          //  delete ui->mapField->scene();
        mapcontainer.setcellsize(ui->cellsize->value());
        ui->mapField->setScene(mapcontainer.drawclearmap(curcolors));
        ui->stepsSlider->setMaximum(logcontainer.numofsteps());
        ui->stepsSlider->setValue(curstep);
        ui->numofsteps->setText(QString::number(logcontainer.numofsteps()));
        ui->stepNum->setValidator( new QIntValidator(0, logcontainer.numofsteps(), this) );
        ui->stepNum->setText("0");        
    }

    if(!maploaded)
    {
        ui->lError->setText(error);
        ui->lError->setVisible(true);
        ui->closeError->setVisible(true);
    }
}

bool MainWindow::openfile(QString filename, QString& error)
{

    TiXmlDocument doc(filename.toStdString().c_str());
    if(!doc.LoadFile())
    {
        error=QString::fromUtf8("File structure is broken");
        return false;
    }

    TiXmlElement *root=doc.FirstChildElement("root");
    if(!root)
    {
        error=QString("No root tag found");
        return false;
    }

    mapcontainer=Map();
    if(!root->FirstChildElement("map"))
    {
        error=QString("No map tag found");
        return false;
    }

    bool parsed=mapcontainer.parseMap(root->FirstChildElement("map"),error);
    if(!parsed)
        return false;

    logcontainer=LogContainer();
    if(!root->FirstChildElement("log"))
    {
        error=QString("No log tag found");
        return false;
    }
    parsed=logcontainer.parseLog(root->FirstChildElement("log"),error);
    curstep=0;
    return parsed;
}




void MainWindow::showstep(int stepnum)
{

    curstep=stepnum;
    ui->stepsSlider->setValue(curstep);
    ui->stepNum->setText(QString::number(curstep));


    for(QGraphicsItem* it : group)
        delete it;
    group.clear();
//    if(curstep==0)
//        ui->mapField->setScene(mapcontainer.drawclearmap(curcolors));
    if(curstep!=0)
    {
        QGraphicsScene *scene=ui->mapField->scene();
        group+=logcontainer.showGlobalStep(scene,stepnum,curcolors,mapcontainer.getcellsize(),ui->showArrows->isChecked(), ui->checkBox->isChecked());


    }
}

void MainWindow::on_stepForward_clicked()
{
    if(maploaded)
    {
        if(curstep==(logcontainer.numofsteps()))
            return;

        showstep(curstep+1);
    }
}


void MainWindow::on_stepBack_clicked()
{
    if(maploaded)
    {
        if(curstep==0)
            return;
        else
            showstep(curstep-1);
    }
}


void MainWindow::on_toBegin_clicked()
{
    if(maploaded)
        showstep(0);
}

void MainWindow::on_toEnd_clicked()
{
    if(maploaded)
        showstep(logcontainer.numofsteps());
}

void MainWindow::on_showArrows_clicked(bool checked)
{
    if(maploaded)
        if(curstep!=0)
            showstep(curstep);
}



void MainWindow::on_cellsize_valueChanged(int arg1)
{

    mapcontainer.setcellsize(arg1);
    delete ui->mapField->scene();
    group.clear();
    ui->mapField->setScene(mapcontainer.drawclearmap(curcolors));
    if(maploaded)
        showstep(curstep);
}


void MainWindow::on_mapField_mouseMoveEvent(QMouseEvent *e)
{
    if((!maploaded)||(curstep<=0))
        return;
    int cellsize=mapcontainer.getcellsize();

    QPointF point=ui->mapField->mapToScene(e->x(),e->y());

//    if(!group.contains(ui->mapField->itemAt(e->x(),e->y())))
//        return;
    int x=point.x(),y=point.y();

    x/=cellsize;
    y/=cellsize;
    if((pointerx!=x)||(pointery!=y))
    {
        if(window)
        {
            window->hide();
        }

        pointerx=x;
        pointery=y;
        if((curstep!=0))
        {
            showstep(curstep);
            QGraphicsScene *scene=ui->mapField->scene();
            group+=logcontainer.showArrowsOfPoint(scene,curstep,curcolors,cellsize,pointerx,pointery);
            ui->mapField->setScene(scene);
        }

        Point p;
        if(logcontainer.findPoint(curstep,pointerx,pointery,p))
        {
            QPalette Pal(palette());
            Pal.setColor(QPalette::Background, Qt::black);
            if(!window)
                window=new InfoWindow(ui->mapField);
            window->setValues(p.f,p.g,p.k,p.label,p.pathfound);
            int xposition=(pointerx+1)*cellsize+10;
            if(p.x<p.parent_x)
                xposition=(pointerx+1)*cellsize-100;

            int yposition=(pointery+1)*cellsize+10;
            QPoint windowleftpoint=ui->mapField->mapFromScene(xposition,yposition);
            if((windowleftpoint.rx()+window->width())>ui->mapField->width())
                xposition=(pointerx)*cellsize-window->width()-10;
            if((windowleftpoint.ry()+window->height())>ui->mapField->height())
                yposition=(pointery)*cellsize-window->height()-10;
            window->move(ui->mapField->mapFromScene(xposition,yposition));
            window->setAutoFillBackground(true);
            window->setPalette(Pal);
            window->show();
        }
    }
}


void MainWindow:: dropEvent(QDropEvent* event){
    QList<QUrl> urls = event->mimeData()->urls();
        if (urls.isEmpty())
            return;
    ui->lError->setVisible(false);
    ui->closeError->setVisible(false);
    QString error;
    QString filename=urls.first().toLocalFile();
    this->setWindowTitle(filename);
    maploaded=openfile(urls.first().toLocalFile(),error);
    if(maploaded)
    {
        if(ui->mapField->scene())
            delete ui->mapField->scene();
        mapcontainer.setcellsize(ui->cellsize->value());
        ui->mapField->setScene(mapcontainer.drawclearmap(curcolors));
        ui->stepsSlider->setMaximum(logcontainer.numofsteps());
        ui->numofsteps->setText(QString::number(logcontainer.numofsteps()));
        ui->stepNum->setValidator( new QIntValidator(0, logcontainer.numofsteps(), this) );
        ui->stepNum->setText("0");
    }
    else
    {

        ui->lError->setText(error);
        ui->lError->setVisible(true);
        ui->closeError->setVisible(true);
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
 if(event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void MainWindow::on_colorcontrol_triggered()
{
    colorwindow->show();
    colorwindow->setcolors(curcolors);
}

void MainWindow::on_closeError_clicked()
{
    ui->lError->setVisible(false);
    ui->closeError->setVisible(false);
}


void MainWindow::on_stepsSlider_sliderMoved(int position)
{
    if(maploaded)
        showstep(position);
}

void MainWindow::on_stepsSlider_valueChanged(int value)
{
    if(maploaded)
        showstep(value);
}

void MainWindow::on_wheel_rounded(int val)
{
    if(maploaded)    
        if((mapcontainer.getcellsize()+val>5)&&(mapcontainer.getcellsize()+val<101))
            ui->cellsize->setValue(mapcontainer.getcellsize()+val);


}

void MainWindow::on_stepNum_textChanged(const QString &arg1)
{
    if(maploaded)
        showstep(arg1.toInt());
}

void MainWindow::on_mapField_mousePressEvent(QMouseEvent *e)
{

    if((!maploaded)||(curstep<=0))
        return;
    int cellsize=mapcontainer.getcellsize();

    QPointF point=ui->mapField->mapToScene(e->x(),e->y());

    int x=point.x(),y=point.y();

    x/=cellsize;
    y/=cellsize;
    group+=logcontainer.showPathToPoint(ui->mapField->scene(),curstep,curcolors,cellsize,x,y);


}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(maploaded)
        if(curstep!=0)
            showstep(curstep);
}
