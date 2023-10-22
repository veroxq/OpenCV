#ifndef FACEANDSMILETESTWINDOW_H
#define FACEANDSMILETESTWINDOW_H


#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QTimer>

class faceAndSmileTestWindow : public QWidget
{
    Q_OBJECT
public:
    faceAndSmileTestWindow(QWidget * parent = 0);
    cv::Mat passFrame;
    int handleModeCondition;

public:
    void showTrue();
    void showFalse();

    void faceCheck_set();
    void smileCheck_set();
    
    int getHandleConditon();
    int getContentConditon();
    QString getContentPath();

    void showImage(QImage qimage);

signals:
    void work_signal();

    
private:
    QLabel * backgroundImageLabel;
    QPixmap * backgroundImage;
    QLabel * imageLabel;
    bool condition;

private:
    void getPictureClicked();
    void getVideoClicked();
    void getCameraClicked();
    void openCamera();
    void closeCamera();
    void updateCamera();

private:
    QPushButton * getPictureButton;
    QPushButton * getVideoButton;
    QPushButton * getCameraButton;
    QPushButton * workStartButton;

    QLineEdit * getPictureText;
    QLineEdit * getVideoText;
    QLineEdit * getCameraText;

    QString contentPath;

    int contentModeCondition;


    cv::VideoCapture capture;
    QTimer * cameraTime;

    bool cameraOpen;
    bool worktrue;
    void work();
public:
    void init();
};

#endif // FACEANDSMILETESTWINDOW_H
