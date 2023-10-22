#ifndef REMINDWINDOW_H
#define REMINDWINDOW_H

#include <QDialog>
#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>


class remindWindow : public QDialog
{
     Q_OBJECT
public:
    remindWindow(QWidget *parent = 0);
    void set(const QString &imagePath);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    QLabel * label;
    QString path;
};

#endif // REMINDWINDOW_H
