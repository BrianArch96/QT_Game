#include "mainwindow.h"

#include <QApplication>
#include <map>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "globals.h"

// Define extern variables
GameTextbox *globals::textbox;
QString *globals::currentItem;
inventoryframe *globals::inventory;

bool globals::hasLockpick = false;
bool globals::hasGrapplingHook = false;
bool globals::hasSkelly = false;
bool globals::openedTreasureDoor = false;
bool globals::hasVisitedBar = false;
bool globals::hasOpenedLock = false;

int globals::currentAnimal = 0;
int globals::currentCountry = 0;
int globals::currentCocktail = 0;
int globals::customerCocktail;
bool globals::barPuzzleFinished = false;

bool globals::shotGrappleHook = false;

#include "gametextbox.h"
#include "dungeondata.h"

int main(int argc, char *argv[])
{
    // Randomly generate the customer's favourite cocktail for the bar puzzle
    srand(time(NULL));
    int animal = pow(2, rand() % 5);
    int country = pow(2, rand() % 5 + 5);
    globals::customerCocktail = animal | country;

    //*
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
    //*/
}

