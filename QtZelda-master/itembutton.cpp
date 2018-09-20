#include "itembutton.h"

itemButton::itemButton(QString name)
{
    this->name = name;
    this->setObjectName(name);
}

void itemButton::clickedItem(bool checked, QString name){
}
