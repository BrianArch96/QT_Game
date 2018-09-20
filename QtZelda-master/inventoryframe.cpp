#include "inventoryframe.h"
#include "ui_inventoryframe.h"
#include "globals.h"
#include <sound.h>

/* Constructor*/
inventoryframe::inventoryframe(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::inventoryframe)
{
    ui->setupUi(this);
    inv = new Inventory();
    col = 0;
    row = 0;
    invSize = 10;
    globals::inventory = this;
    //invButtons = new QList<QPushButton>();
}

/* Deconstructor*/
inventoryframe::~inventoryframe()
{
    delete ui;
}

/* Updates drop down boxes to match inventory*/
void inventoryframe::updateInventory(){
    //Clears item make drop down boxes
    ui->itemMake1->clear();
    ui->itemMake2->clear();
    //Adds all items in inventory to item make drop down boxes
    for(int i = 0; i < inv->getSize(); i++){
        ui->itemMake1->addItem(inv->getItem(i));
        ui->itemMake2->addItem(inv->getItem(i));
    }
}

/* Add item to inventory*/
void inventoryframe::addToInventory(QString itemName){

    // Update global flags, as necessary
    if (itemName == "GrappleHook")
        globals::hasGrapplingHook = true;

    else if (itemName == "Skelly")
        globals::hasSkelly = true;

    else if (itemName == "Cocktail")
        globals::currentCocktail = globals::currentAnimal
                                 | globals::currentCountry;
    else if (itemName == "LockPick")
        globals::hasLockpick = true;

    //Adds item string to inventory and updates buttons and drop down box to match
    inv->addItem(itemName);
    updateButtons();
    updateInventory();
}

/* Adds item button*/
void inventoryframe::addItemButtons(QString itemName){
    itemButton* tempButton = new itemButton(itemName);

    //Sets image for button
    QString fileName = itemName + "Icon.png";
    tempButton->setStyleSheet("border-image:url(:" + fileName + ");max-width: 50px;max-height: 50px;");

    //Adds button to gridlayout in grid
    ui->gridLayout->addWidget(tempButton,row,col);
    col++;
    if(col > 2){
        col = 0;
        row++;
    }
    connect(tempButton, SIGNAL(clicked()), this, SLOT(on_itemButton_clicked()));
    invButtons.push_back(tempButton);
}

/* Updates buttons to match whats in the inventory*/
void inventoryframe::updateButtons(){
    col = 0;
    row = 0;
    //Remove all items from grid layout
    QLayoutItem* item;
    while((item = ui->gridLayout->takeAt(0)) != NULL){
        delete item->widget();
        delete item;
    }
    //Remove all items from inventory buttons
    invButtons.clear();
    for(int i = 0; i < inv->getSize(); i++){
        addItemButtons(inv->getItem(i));
    }
}

/* Checks current item(UNUSED)*/
QString inventoryframe::checkCurrentItem(){
    return inv->getCurrentItem();
}

/* Removes item from inventory with itemName as name*/
void inventoryframe::removeFromInventory(QString itemName){
    //Delete items used
    inv->removeItem(itemName);

    //Delete buttons used
    updateButtons();
    updateInventory();
}

/* Used to change currentItem text*/
void inventoryframe::on_itemButton_clicked()
{
    QString itemName = sender()->objectName();
    inv->setCurrentItem(itemName);
}

/* Make item button will check what is in the drop down boxes and make a recipe with them in it*/
void inventoryframe::on_makeItemButton_clicked()
{
    QVector<QString> recipes = inv->getRecipes();
    bool done = false;
    //Finding recipe that matches the items in drop down
    for(int i = 0; i < recipes.length() && !done; i++){
        QStringList recipe = recipes.at(i).split("/");
        bool match = false;

        if(QString::compare(ui->itemMake1->currentText(),recipe.at(0)) == 0){
            if(QString::compare(ui->itemMake2->currentText(),recipe.at(1)) == 0){
                match = true;
            }
        }
        if(QString::compare(ui->itemMake1->currentText(),recipe.at(1)) == 0){
            if(QString::compare(ui->itemMake2->currentText(),recipe.at(0)) == 0){
                match = true;
            }
        }
        if(match){
            //Adding new item to buttons and inventory
            addToInventory(recipe.at(2));
            done = true;

            //Delete items used
            removeFromInventory(recipe.at(0));
            removeFromInventory(recipe.at(1));

            updateButtons();
        }
    }
}
