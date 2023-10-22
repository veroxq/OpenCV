#include "camera.h"

Camera::Camera(QObject *parent) : QObject(parent)
{

}
Camera::~Camera(){
    closeCamera();
}

void Camera::openCamera()
{
    cameraObj.open(0);

    //摄像头打开失败
    if(!cameraObj.isOpened()){
        QMessageBox msgBox;
        msgBox.setWindowTitle("摄像头操作错误");
        msgBox.setText("摄像头打开失败");
        msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Retry);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Retry) {
            openCamera();
        }
    }
    //捕获帧失败
    while(true)
    {
        cv::Mat frame;
        emit cameraOpenSuccess();
        if(!cameraObj.read(frame))
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("摄像头操作错误");
            msgBox.setText("捕获帧失败");
            msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Retry);
            int ret = msgBox.exec();
            if (ret == QMessageBox::Retry) {
                openCamera();
            }
            break;
        }

        QImage image(frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
        emit frameCaptured(image);
    }
}
void Camera::closeCamera()
{
    if(cameraObj.isOpened())
    {
        cameraObj.release();
    }
}
