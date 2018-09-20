#ifndef INVENTORYFRAME_H
#define INVENTORYFRAME_H

#include <QFrame>
#include <QString>
#include "inventory.h"
#include "itembutton.h"

namespace Ui {
class inventoryframe;
}

class inventoryframe : public QFrame
{
    Q_OBJECT

public:
    explicit inventoryframe(QWidget *parent = 0);
    ~inventoryframe();
    void updateInventory();
    void addToInventory(QString itemName);
    void removeFromInventory(QString itemName);
    QString checkCurrentItem();
    int col;
    int row;

private slots:
    void on_makeItemButton_clicked();

    void on_itemButton_clicked();

private:
    Ui::inventoryframe *ui;
    Inventory *inv;
    void addItemButtons(QString itemName);
    void updateButtons();
    QList<itemButton *> invButtons;
    int invSize;
};

#endif // INVENTORYFRAME_H
