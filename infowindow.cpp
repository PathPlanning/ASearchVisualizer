#include "infowindow.h"
#include "ui_infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) :
    QWidget(parent,Qt::CustomizeWindowHint ),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
}

InfoWindow::~InfoWindow()
{
    delete ui;
}


void InfoWindow::setValues(double f, double g, int k, QString label, QString pathf)
{
    ui->f->setText(QString::number(f));
    ui->g->setText(QString::number(g));
    ui->label->setText(QString::number(f-g));
}
