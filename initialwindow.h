#ifndef INITIALWINDOW_H
#define INITIALWINDOW_H

#include <QWidget>
#include <QLabel>

class initialWindow : public QWidget
{
   Q_OBJECT
public:
    initialWindow(QWidget * parent);
    QLabel * backgroundImageLabel;
    QPixmap * backgroundImage;

};

#endif // INITIALWINDOW_H
