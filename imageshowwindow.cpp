#include "imageshowwindow.h"

imageShowWindow::imageShowWindow(QWidget *parent) : QDialog(parent)
{

}

void imageShowWindow::set(const QImage &qimage){

    setWindowFlags(Qt::FramelessWindowHint);

    QPixmap pixmap = QPixmap::fromImage(qimage);
    label = new QLabel(this);
    label->setPixmap(pixmap.scaled(size(), Qt::KeepAspectRatioByExpanding)); // 缩放图片以适应窗口大小


    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);


    setLayout(layout);
}

void imageShowWindow::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    close();
}

void imageShowWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
}
