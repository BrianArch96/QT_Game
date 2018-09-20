#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include <QPushButton>

class itemButton : public QPushButton
{
public:
    itemButton(QString name);
private:
    QString name;
Q_SIGNALS:
    void clickedItem(bool checked = false, QString name = "");

};

#endif // ITEMBUTTON_H
