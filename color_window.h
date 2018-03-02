#ifndef COLOR_WINDOW_H
#define COLOR_WINDOW_H

#include <QDialog>
#include <QColorDialog>
#include "colors.h"

namespace Ui {
class color_window;
}

class color_window : public QDialog
{
    Q_OBJECT
    
public:
    explicit color_window(QWidget *parent = 0);
    ~color_window();
    void setcolors(Colors *colorset);

private slots:
    void changecolor();
    void on_pushButton_clicked();

private:
    Ui::color_window *ui;
    Colors *curcolors;
    QWidget *parent;

};

#endif // COLOR_WINDOW_H
