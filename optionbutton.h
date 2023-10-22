#ifndef OPTIONBUTTON_H
#define OPTIONBUTTON_H
#include <QString>
#include <QPushButton>
#include <QPixmap>
class OptionButton : public QPushButton
{
    Q_OBJECT

public:
    OptionButton(QWidget * parent = 0);

    void setImages(const QString &normalImagePath,const QString &highlightImagePath);
    void reset();
    void set();
private:
    QString normalImage;
    QString highlightImage;
    bool condition;
};

#endif // OPTIONBUTTON_H
