#include "color_window.h"
#include "ui_color_window.h"
#include <iostream>

color_window::color_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::color_window)
{
    ui->setupUi(this);
    connect(ui->cGoal, SIGNAL(clicked()),this, SLOT(changecolor()));
    connect(ui->cObst, SIGNAL(clicked()),this, SLOT(changecolor()));
    connect(ui->cStart, SIGNAL(clicked()),this, SLOT(changecolor()));
    connect(ui->cGoalPath, SIGNAL(clicked()),this, SLOT(changecolor()));
    connect(ui->cGlobalClose, SIGNAL(clicked()),this, SLOT(changecolor()));
    connect(ui->cGlobalOpen, SIGNAL(clicked()),this, SLOT(changecolor()));
    connect(ui->cUndefArrow, SIGNAL(clicked()),this, SLOT(changecolor()));
    connect(ui->cFreeArrow, SIGNAL(clicked()),this, SLOT(changecolor()));
    connect(ui->cPathColor, SIGNAL(clicked()),this, SLOT(changecolor()));
}

color_window::~color_window()
{
    delete ui;
}

void color_window::changecolor()
{
    QCommandLinkButton *cButton=(QCommandLinkButton*) QObject::sender();
    QColor color;
    if(cButton==ui->cGoal)
        color=curcolors->goal;
    else if(cButton==ui->cObst)
        color=curcolors->obst;
    else if(cButton==ui->cStart)
        color=curcolors->start;
    else if(cButton==ui->cGoalPath)
        color=curcolors->goalpath;
    else if(cButton==ui->cGlobalClose)
        color=curcolors->globalclose;
    else if(cButton==ui->cGlobalOpen)
        color=curcolors->globalopen;
    else if(cButton==ui->cUndefArrow)
        color=curcolors->undefarrow;
    else if(cButton==ui->cFreeArrow)
        color=curcolors->freearrow;
    else if(cButton==ui->cPathColor)
        color=curcolors->pathcolor;

    color=QColorDialog::getColor(color,this);
    if(color.isValid())
    {
        QPalette pal;
        pal.setColor(QPalette::Button, color);
        cButton->setPalette(pal);
        if(cButton==ui->cGoal)
            curcolors->goal=color;
        else if(cButton==ui->cObst)
            curcolors->obst=color;
        else if(cButton==ui->cStart)
            curcolors->start=color;
        else if(cButton==ui->cGoalPath)
            curcolors->goalpath=color;
        else if(cButton==ui->cGlobalClose)
            curcolors->globalclose=color;
        else if(cButton==ui->cGlobalOpen)
            curcolors->globalopen=color;
        else if(cButton==ui->cUndefArrow)
            curcolors->undefarrow=color;
        else if(cButton==ui->cFreeArrow)
            curcolors->freearrow=color;
        else if(cButton==ui->cPathColor)
            curcolors->pathcolor=color;
    }
}

void color_window::setcolors(Colors *colorset)
{
    this->curcolors=colorset;
    ui->cObst->setPalette(QPalette(curcolors->obst));
    ui->cStart->setPalette(QPalette(curcolors->start));
    ui->cGoal->setPalette(QPalette(curcolors->goal));
    ui->cGoalPath->setPalette(QPalette(curcolors->goalpath));
    ui->cGlobalClose->setPalette(QPalette(curcolors->globalclose));
    ui->cGlobalOpen->setPalette(QPalette(curcolors->globalopen));
    ui->cUndefArrow->setPalette(QPalette(curcolors->undefarrow));
    ui->cFreeArrow->setPalette(QPalette(curcolors->freearrow));
    ui->cPathColor->setPalette(QPalette(curcolors->pathcolor));
}


void color_window::on_pushButton_clicked()
{
    this->destroyed();
    this->close();
}
