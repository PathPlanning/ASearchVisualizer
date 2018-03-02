#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QSettings>
#include <string>
#include <QCheckBox>
#include <QFileDialog>
#include <QUrl>
#include <QMimeData>
#include <QScrollBar>

#include "infowindow.h"
#include "tinyxml/tinyxml.h"
#include "map.h"
#include "logcontainer.h"
#include "colors.h"
#include "point.h"
#include "color_window.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    bool maploaded;
    InfoWindow *window;
    LogContainer logcontainer;
    Map mapcontainer;
    bool openfile(QString filename, QString &error);
    void showstep(int stepnum);
    Colors *curcolors;
    int curstep;
    int pointerx,pointery;
    color_window* colorwindow;
    QGraphicsScene *clearmap;

    QVector<QGraphicsItem*> group;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent* event);
private slots:
    void on_openfilemenuaction_triggered();
    void on_colorcontrol_triggered();
    void on_stepForward_clicked();
    void on_stepBack_clicked();
    void on_toBegin_clicked();
    void on_toEnd_clicked();
    void on_showArrows_clicked(bool checked);
    void on_cellsize_valueChanged(int arg1);
    void on_mapField_mouseMoveEvent(QMouseEvent *);
    void on_closeError_clicked();
    void on_stepsSlider_sliderMoved(int position);
    void on_stepsSlider_valueChanged(int value);
    void on_wheel_rounded(int val);
    void on_stepNum_textChanged(const QString &arg1);

    void on_mapField_mousePressEvent(QMouseEvent *);
    void on_checkBox_clicked(bool checked);
};

#endif // MAINWINDOW_H
