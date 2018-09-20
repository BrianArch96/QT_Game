#include "inventory.h"
#include "globals.h"

Inventory::Inventory()
{
    //Sets current item
    currentItem = "";
    globals::currentItem = &this->currentItem;

    //Add recipes
    itemRecipes.push_back("Rope/Hook/GrappleHook");
    itemRecipes.push_back("Head/Body/Head+Body");
    itemRecipes.push_back("Body/Legs/Body+Legs");
    itemRecipes.push_back("Head/Body+Legs/Skelly");
    itemRecipes.push_back("Head+Body/Legs/Skelly");
    itemRecipes.push_back("Knife/Pick/LockPick");
    int n = 5;
    QString countrys [n] = {"IREDrink", "SPADrink", "ITADrink", "POLDrink", "RUSDrink"};
    QString animals [n] = {"RavenDrink", "WolfDrink", "TigerDrink", "HippoDrink", "WhaleDrink"};
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            QString recipe = countrys[i] + "/" + animals[j] + "/Cocktail";
            itemRecipes.push_back(recipe);
        }
    }
}

void Inventory::addItem(QString item)
{
    items.push_back(item);
}

void Inventory::removeItem(QString item)
{
    int itemLoaction = items.indexOf(item);
    items.removeAt(itemLoaction);
}

void Inventory::addItemButton(QPushButton *item)
{
    itemButtons.push_back(item);
}

QString Inventory::getItem(int index)
{
    return items.value(index);
}

int Inventory::getSize()
{
    return items.size();
}

QVector<QString> Inventory::getRecipes()
{
    return itemRecipes;
}


QString Inventory::getCurrentItem()
{
    return currentItem;
}

void Inventory::setCurrentItem(QString currentItem)
{
    this->currentItem = currentItem;
    globals::currentItem = &this->currentItem;
}

QString Inventory::getItemsAsString()
{
    QString invAsString = "";
    for(int i = 0; i < items.size(); i++){
        invAsString += items.at(i) + " ";
    }
    return invAsString;
}
