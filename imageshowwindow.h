#ifndef IMAGESHOWWINDOW_H
#define IMAGESHOWWINDOW_H
#include <QDialog>
#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QImage>

class imageShowWindow: public QDialog
{
    Q_OBJECT
public:
    imageShowWindow(QWidget *parent = 0);
    void set(const QImage &qimage);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
private:
    QLabel * label;
    QString path;
};

#endif // IMAGESHOWWINDOW_H
