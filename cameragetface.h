#ifndef CAMERAGETFACE_H
#define CAMERAGETFACE_H

#include <QImage>
#include <QWidget>
#include <QImage>
#include <QPushButton>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

class cameraGetFace : public QDialog
{
    Q_OBJECT
public:
    cameraGetFace(QWidget * parent = 0);


    QImage getImage();
    void openWindow();
private:
    QPushButton * button;
    cv::VideoCapture capture;
    cv::Mat frame;

    QImage faceImage;
    QLabel * label;
    QTimer * timer;

    void ok();
    void update();
};

#endif // CAMERAGETFACE_H
