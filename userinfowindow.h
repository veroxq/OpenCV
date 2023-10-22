#ifndef USERINFOWINDOW_H
#define USERINFOWINDOW_H

#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QPushButton>
#include <userinfo.h>
class userInfoWindow : public QWidget
{
    Q_OBJECT
public:
    userInfoWindow(QWidget * parent = 0);
    void showWindow();
    void hideWindow();

public slots:
    void set(userInfo user);

private:
    cv::Mat face;

    QLabel * backgroundImageLabel;
    QLabel * nameLabel;
    QLabel * idLabel;
    QLabel * genderLabel;
    QLabel * ageLabel;
    QLabel * faceLabel;
    QPushButton * closeButton;

};

#endif // USERINFOWINDOW_H
