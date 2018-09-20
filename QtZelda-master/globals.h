#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
#include "gametextbox.h"
#include "inventoryframe.h"

#define SIGN(X) ((X == 0) ? 0 : (X > 0 ? 1 : -1))
#define ABS(X) (X > 0 ? X : -X)
#define MIN(A, B) (A < B ? A : B)
#define MAX(A, B) (A > B ? A : B)

namespace globals {
static const double FADE_SPEED = 0.0075;
static const int CELL_SIZE = 48;
static const int GRID_W = 13;
static const int GRID_H = 10;

extern GameTextbox* textbox;
extern QString* currentItem;
extern inventoryframe* inventory;

extern bool hasLockpick;
extern bool hasOpenedLock;
extern bool hasGrapplingHook;
extern bool hasSkelly;
extern bool openedTreasureDoor;
extern bool hasVisitedBar;

// Constants for bar puzzle
static const int ANIMAL_RAVEN = 1;     // 0000000001
static const int ANIMAL_WOLF = 2;      // 0000000010
static const int ANIMAL_TIGER = 4;     // 0000000100
static const int ANIMAL_HIPPO = 8;     // 0000001000
static const int ANIMAL_WHALE = 16;    // 0000010000
static const int COUNTRY_IRE = 32;     // 0000100000
static const int COUNTRY_SPA = 64;     // 0001000000
static const int COUNTRY_ITA = 128;    // 0010000000
static const int COUNTRY_POL = 256;    // 0100000000
static const int COUNTRY_RUS = 512;    // 1000000000

// Variables specific to the bar puzzle
extern int currentAnimal;
extern int currentCountry;
extern int currentCocktail;
extern int customerCocktail;    // The cocktail which the customer wants
extern bool barPuzzleFinished;  // Set to true when the bar puzzle is over

extern bool shotGrappleHook;    // Set to true when the player has used hook
}

#endif // GLOBALS_H
