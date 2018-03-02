#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>

namespace Ui {
class InfoWindow;
}

class InfoWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit InfoWindow(QWidget *parent = 0);
    void setValues(double f, double g, int k, QString label, QString pathf);
    ~InfoWindow();
    
private:
    Ui::InfoWindow *ui;
};

#endif // INFOWINDOW_H
