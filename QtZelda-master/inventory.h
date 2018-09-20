#ifndef INVENTORY_H
#define INVENTORY_H
#include <QVector>
#include <QPushButton>


class Inventory
{
public:
    Inventory();
    void addItem(QString item);
    void removeItem(QString item);
    void addItemButton(QPushButton *item);
    QString getCurrentItem();
    void setCurrentItem(QString currentItem);
    int getSize();
    QVector<QString> getRecipes();
    QString getItem(int index);
    QString getItemsAsString();
private:
    QVector<QString> items;
    QVector<QString> itemRecipes;
    QVector<QPushButton *> itemButtons;
    QString currentItem;
};

#endif // INVENTORY_H
