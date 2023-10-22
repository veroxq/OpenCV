#include "remindwindow.h"
#include <QDialog>


remindWindow::remindWindow(QWidget *parent) : QDialog(parent)
{

}
void remindWindow::set(const QString &imagePath){
   path=imagePath;

   setWindowFlags(Qt::FramelessWindowHint);

   QPixmap pixmap(path);
   label = new QLabel(this);
   label->setPixmap(pixmap.scaled(size(), Qt::KeepAspectRatioByExpanding)); // 缩放图片以适应窗口大小


   QVBoxLayout *layout = new QVBoxLayout(this);
   layout->addWidget(label);


   setLayout(layout);
}

void remindWindow::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    close();
}

void remindWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
}
