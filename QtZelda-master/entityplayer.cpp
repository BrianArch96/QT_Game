#include "entityplayer.h"

#include <Qt>
#include <iostream>
#include "input.h"
#include "sound.h"
#include "globals.h"

EntityPlayer::EntityPlayer(int x, int y)
    : Entity(":man.png", globals::CELL_SIZE, globals::CELL_SIZE),
      currentRow(x), currentCol(y),
      speed(4),
      moving(false), canMove(true)
{
    int s = globals::CELL_SIZE;

    posX = (currentCol + 0.5) * s;
    posY = (currentRow + 0.5) * s;

    // Set up the player's animation
    std::vector<QRect> animRects;
    animRects.push_back(QRect(0, 0, s, s));
    animRects.push_back(QRect(0, s, s, s));
    animRects.push_back(QRect(0, 0, s, s));
    animRects.push_back(QRect(0, s*2, s, s));

    animation = new Animation(0.15, animRects);
}

void EntityPlayer::setWorld(DungeonData::TileType *world, int rows, int cols)
{
    // Copy world data
    /*
    this->world =
            (DungeonData::TileType*)malloc(sizeof(DungeonData::TileType) * rows * cols);
    memcpy(this->world, world, sizeof(DungeonData::TileType) * rows * cols);
    */

    this->world = world;

    //worldNumRows = rows;
    //worldNumCols = cols;

    worldNumRows = globals::GRID_H;
    worldNumCols = globals::GRID_W;
}

void EntityPlayer::tick()
{
    if (moving)
    {
        // Animate the player
        animation->tick(0.016);

        // The player's destination
        int destX = currentCol * globals::CELL_SIZE + globals::CELL_SIZE/2;
        int destY = currentRow * globals::CELL_SIZE + globals::CELL_SIZE/2;

        // The distance to the destination
        int distX = destX - posX;
        int distY = destY - posY;

        if (distX == 0 && distY == 0)
        {
            // The player is at his destination, stop moving
            moving = false;
        }
        else
        {
            // Move the player toward the destination
            posX += MIN(ABS(distX), speed) * SIGN(distX);
            posY += MIN(ABS(distY), speed) * SIGN(distY);
        }
    }

    else
    {
        animation->tick(0.016);

        // Handle input
        if (canMove)
        {
            moving = true;
            canMove = false;

            bool hasMoved = false;

            // Move Up
            if (Input::getInstance()->getKey(Qt::Key_W)) {
                rotation = 180;
                if (canMoveTo(0, -1)) {
                    currentRow -= 1;
                    Sound::getInstance()->playCharacterMoving("walking");
                    hasMoved = true;
                }
            }
            // Move Down
            else if (Input::getInstance()->getKey(Qt::Key_S)) {
                rotation = 0;
                if (canMoveTo(0, 1)) {
                    currentRow += 1;
                    Sound::getInstance()->playCharacterMoving("walking");
                    hasMoved = true;
                }
            }
            // Move Left
            else if (Input::getInstance()->getKey(Qt::Key_A)) {
                rotation = 90;
                if (canMoveTo(-1, 0)) {
                    currentCol -= 1;
                    Sound::getInstance()->playCharacterMoving("walking");
                    hasMoved = true;
                }
            }
            // Move Right
            else if (Input::getInstance()->getKey(Qt::Key_D)) {
                rotation = 270;
                if (canMoveTo(1, 0)) {
                    currentCol += 1;
                    Sound::getInstance()->playCharacterMoving("walking");
                    hasMoved = true;
                }
            }
            // Interact
            else if (Input::getInstance()->getKeyJustPressed(Qt::Key_E)) {
                interact(currentCol, currentRow);
                hasMoved = true;
            }
            /*
            // <<for testing, instantly give the player key items>>
            else if (Input::getInstance()->getKeyJustPressed(Qt::Key_P)) {
                globals::inventory->addToInventory("GrappleHook");
                globals::inventory->addToInventory("Skelly");
            }
            */
            // Don't move
            if (!hasMoved){
                canMove = true;
                moving = false;

                animation->stop();
            }
            else
            {
                // Reduce speed if player moved onto rope
                if (world[currentCol + currentRow * worldNumCols]
                        == DungeonData::CHASM_ROPE)
                    speed = 2.5;
                else
                    speed = 4;
            }
        }
    }
}

void EntityPlayer::render(QPainter *painter)
{
    Entity::render(painter);
}

Entity::EntityType EntityPlayer::getType()
{
    return PLAYER;
}

bool EntityPlayer::getMoving()
{
    return moving;
}

void EntityPlayer::setCanMove(bool canMove)
{
    this->canMove = canMove;
}

std::string EntityPlayer::getMessage()
{
    return message;
}

/* Returns true if the cell at relative position dx and dy can be moved to */
bool EntityPlayer::canMoveTo(int dx, int dy)
{
    // the next cell
    int x = currentCol + dx;
    int y = currentRow + dy;

    // return false if cell is "outside the grid"
    if (x < 0 || x >= worldNumCols || y < 0 || y >= worldNumRows)
        return false;

    // return true if the next tile is not solid (can be walked into)
    return !DungeonData::getSolid(world[x + y * worldNumCols]);
}

/* Interact with the tile at the current position */
void EntityPlayer::interact(int x, int y)
{
    // for use with functions which look for the position of other tiles
    int fx, fy;

    // Handle the tile based on its type
    switch (world[x + y * worldNumCols]) {

    /* Items */
    case DungeonData::ITEM_HOOK:
    case DungeonData::ITEM_ROPE:
    case DungeonData::ITEM_HEAD:
    case DungeonData::ITEM_BODY:
    case DungeonData::ITEM_LEGS:
    case DungeonData::ITEM_KNIFE:
    case DungeonData::ITEM_PICK:
        tryPickupItem(world[x + y * worldNumCols], x, y);
        break;

    /* Test Room */
    case DungeonData::TELEPORTER_A:
        tryTeleport(DungeonData::TELEPORTER_B);
        break;

    case DungeonData::TELEPORTER_B:
        tryTeleport(DungeonData::TELEPORTER_A);
        break;

    case DungeonData::MARIO_TALK:
        if (rotation == 180)
            globals::textbox->addText("Mario", "wahoo!");
        break;

    /* Intro Room */
    case DungeonData::LEVER_A_OFF:
        // Look for DOOR_A
        if (getLocation(DungeonData::DOOR_A_CLOSED, &fx, &fy)) {
            // Open the door
            world[fx + fy * worldNumCols] = DungeonData::DOOR_A_OPEN;
        }

        // Change the lever to be on
        world[x + y * worldNumCols] = DungeonData::LEVER_A_ON;
        break;

    case DungeonData::DOOR_A_OPEN:
        moveToState("hub", 0);
        break;

    case DungeonData::INTRO_HOLE:
        moveToState("hub", 0);
        break;

    case DungeonData::INTRO_LOCK_INTERACT:
        if (globals::hasLockpick && getLocation(DungeonData::INTRO_LOCK_CLOSED, &fx, &fy))
        {
            // Open the lock
            world[fx + fy * worldNumCols] = DungeonData::INTRO_LOCK_OPEN;

            // Remove the lockpick
            globals::inventory->removeFromInventory("LockPick");
            globals::hasOpenedLock = true;
        }
        break;

    case DungeonData::INTRO_NPC_INTERACT:
        if (rotation == 90)
        {
            if(!globals::hasOpenedLock)
                globals::textbox->addText("Wario", "Hey boy, you're here for the "
                    "Dungeon, I suppose. Get those items over there and make a "
                    "LockPick. You can do this by selecting them both in the "
                    "drop-down lists in the screen to the left and pressing "
                    "`Make Item`. That should allow you to get past that gate.");
            else
                globals::textbox->addText("Wario", "Please leave now...");
        }
        break;

    /* Teleporter Room */
    case DungeonData::TELEPORTERS_DOOR_EXIT:
        moveToState("hub", 270);
        break;

    // teleporters
    case DungeonData::TELEPORTER_S:         tryTeleport(DungeonData::TELEPORTER_S_DEST); break;
    case DungeonData::TELEPORTER_S_HIDDEN:  tryTeleport(DungeonData::TELEPORTER_S_DEST); break;
    case DungeonData::TELEPORTER_1:         tryTeleport(DungeonData::TELEPORTER_1_DEST); break;
    case DungeonData::TELEPORTER_2:         tryTeleport(DungeonData::TELEPORTER_2_DEST); break;
    case DungeonData::TELEPORTER_3:         tryTeleport(DungeonData::TELEPORTER_3_DEST); break;
    case DungeonData::TELEPORTER_4:         tryTeleport(DungeonData::TELEPORTER_4_DEST); break;
    case DungeonData::TELEPORTER_E:         tryTeleport(DungeonData::TELEPORTER_E_DEST); break;

    /* Hub Room */
    case DungeonData::HUB_DOOR_N_OPEN:
        moveToState("treasure", 0);
        break;

    case DungeonData::HUB_DOOR_S:
        moveToState("chasm", 180);
        break;

    case DungeonData::HUB_DOOR_E:
        moveToState("teleporters", 90);
        break;

    case DungeonData::HUB_DOOR_W:
        moveToState("bar", 270);
        break;

    case DungeonData::HUB_CHAIR_BEFORE:
        if (globals::hasSkelly)
        {
            /*
            if (getLocation(DungeonData::HUB_CHAIR_BEFORE, &fx, &fy))
                world[fx + fy * worldNumCols] = DungeonData::HUB_CHAIR_AFTER;
                */

            // Put Skelly on chair
            world[x + y * worldNumCols] = DungeonData::HUB_CHAIR_AFTER;

            // Make Skelly speak
            globals::textbox->addText("Skelly Talking", "Skelly", "NICE! "
                "Thanks to you, I'm alive again! Let me type in this super "
                "secret password so you can get the crown. Anyhow I will see "
                "games this thing has!");

            Sound::getInstance()->skellySpeak("skelly");

            // Open Treasure Door
            if (getLocation(DungeonData::HUB_DOOR_N_CLOSED, &fx, &fy))
                world[fx + fy * worldNumCols] = DungeonData::HUB_DOOR_N_OPEN;

            // Remove Skelly from inventory
            globals::inventory->removeFromInventory("Skelly");

            // Move player
            posX -=  globals::CELL_SIZE;
            currentCol -= 1;
            rotation = 270;

            // Turn control panel on
            if (getLocation(DungeonData::HUB_CONTROL_PANEL_OFF, &fx, &fy))
                world[fx + fy * worldNumCols] = DungeonData::HUB_CONTROL_PANEL_ON;

            // Set global flag
            globals::openedTreasureDoor = true;
        }
        break;

    // Talk to skelly after he has been seated
    case DungeonData::HUB_CHAIR_INTERACT:
        if (globals::openedTreasureDoor && rotation == 270)
        {
            talkToSkelly();
        }
        break;

    case DungeonData::HUB_CHAIR_INTERACT_2:
        if (globals::openedTreasureDoor && rotation == 180)
        {
            talkToSkelly();
        }
        break;

    // NPC
    case DungeonData::HUB_NPC_INTERACT:
        if (rotation == 180)
        {
            if (!globals::openedTreasureDoor)
//                globals::textbox->addText("Waluigi", "Only one guy knew the "
//                    "password to the treasure room, but he died. Maybe if "
//                    "someone, oh I don't know, some sort of hero, found all "
//                    "his bones, combined them together and put him that "
//                    "control panel they could use him to open the door.");
                globals::textbox->addText("Waluigi", "There was only one guy "
                    "Who knew how to use this control panel, but he died long "
                    "ago, and his bones have been scattered around this dungeon. "
                    "Rumor has it, that if you collect his bones, combine them "
                    "and place the completed skeleton on that purple mat, there, "
                    "he'll come back to life and open the door to a room filled "
                    "with treasure");
            else
                globals::textbox->addText("Waluigi", "I am going to get me some "
                    "of that gold. Thanks buddy!!!");
        }
        if (rotation == 90)
        {
            talkToSkelly();
        }
        break;

    /* Bar Room */
    case DungeonData::BAR_DOOR_EXIT:
        moveToState("hub", 90);
        break;

    // Collect mixers
    // Animals
    case DungeonData::BAR_ANIMAL_RAVEN:
    case DungeonData::BAR_ANIMAL_WOLF:
    case DungeonData::BAR_ANIMAL_TIGER:
    case DungeonData::BAR_ANIMAL_HIPPO:
    case DungeonData::BAR_ANIMAL_WHALE:
        if (rotation == 180)
            tryPickupAnimal(world[x + y * worldNumCols]);
        break;

    // Countries
    case DungeonData::BAR_COUNTRY_IRE:
    case DungeonData::BAR_COUNTRY_SPA:
    case DungeonData::BAR_COUNTRY_ITA:
    case DungeonData::BAR_COUNTRY_POL:
    case DungeonData::BAR_COUNTRY_RUS:
        if (rotation == 0)
            tryPickupCountry(world[x + y * worldNumCols]);
        break;


    case DungeonData::BAR_CUSTOMER_TALK:
        // Make sure the player is facing the customer
        if (rotation == 90)
            handleBarPuzzleLogic();
        break;

    /* Chasm Room */
    case DungeonData::CHASM_DOOR_EXIT:
        moveToState("hub", 180);
        break;

    case DungeonData::CHASM_DOOR_NEXT:
        moveToState("final", 180);
        break;

    case DungeonData::CHASM_HOOK_SPOT:
        if (rotation == 0 && globals::hasGrapplingHook)
        {
            // Affect the anchor rock
            if (getLocation(DungeonData::CHASM_ANCHOR_BEFORE, &fx, &fy)){
                world[fx + fy * worldNumCols] = DungeonData::CHASM_ANCHOR_AFTER;
                Sound::getInstance()->grapplingRock("grappling");
            }

            // Lay out rope
            for (int row = 2; row <= 7; ++row)
                world[2 + row * worldNumCols] = DungeonData::CHASM_ROPE;

            // Sink hook in wall
            world[2 + 8 * worldNumCols] = DungeonData::CHASM_TARGET_WALL_EXTENDED;
            world[2 + 9 * worldNumCols] = DungeonData::CHASM_TARGET_WALL;

            // Remove GrappleHook from inventory
            globals::inventory->removeFromInventory("GrappleHook");

            // Set global flag
            globals::shotGrappleHook = true;
        }
        break;

    case DungeonData::CHASM_MAN_TALK:
        if (rotation == 180)
        {
            if (!globals::shotGrappleHook)
                globals::textbox->addText("Chasm Guy Normal","Luigi", "You will need a grapple hook to get past. I have been looking"
                    " for years with no luck");

            else{
                globals::textbox->addText("Chasm Guy Shocked","Luigi", "Wa...Wa... where did you get that?");
            }
            Sound::getInstance()->characterSpeak("speak");
        }


        break;

    /* Final Room */
    case DungeonData::FINAL_DOOR_EXIT:
        moveToState("chasm", 0);
        break;

    // Levers
    case DungeonData::FINAL_LEVER_A_OFF:
    case DungeonData::FINAL_LEVER_A_ON:
    case DungeonData::FINAL_LEVER_B_OFF:
    case DungeonData::FINAL_LEVER_B_ON:
    case DungeonData::FINAL_LEVER_C_OFF:
    case DungeonData::FINAL_LEVER_C_ON:
    case DungeonData::FINAL_LEVER_D_OFF:
    case DungeonData::FINAL_LEVER_D_ON:
        handleFinalLever(world[x + y * worldNumCols], x, y);
        break;

    /* Treasure Room */
    case DungeonData::TREASURE_DOOR_EXIT:
        moveToState("hub", 180);
        break;

    case DungeonData::TREASURE_CROWN_INTERACT:
        setMessage("fadeend");
        break;
    }
}

void EntityPlayer::talkToSkelly()
{
    globals::textbox->addText("Skelly", "An ancient version of minesweeper "
        "is what I will be playing for eternity.");
    Sound::getInstance()->skellySpeak("skelly");
}

void EntityPlayer::moveToState(std::string name, int rotation)
{
    this->rotation = rotation;

    setMessage("changestate " + name);
    Sound::getInstance()->goThroughDoor("goThroughDoor");
    globals::textbox->hideImage();

    // Do special event the first time you enter the bar
    if (name == "bar" && !globals::hasVisitedBar)
    {
        globals::textbox->addText("Thirsty Guy", "Hey buddy ol' pal come over here!");

        globals::hasVisitedBar = true;
    }
}

bool EntityPlayer::tryPickupItem(DungeonData::TileType tile, int x, int y)
{
    std::string item = "";
    Sound::getInstance()->pickUpItem("pickup");
    switch(tile)
    {
        case DungeonData::ITEM_HOOK: item = "Hook"; break;
        case DungeonData::ITEM_ROPE: item = "Rope"; break;
        case DungeonData::ITEM_HEAD: item = "Head"; break;
        case DungeonData::ITEM_BODY: item = "Body"; break;
        case DungeonData::ITEM_LEGS: item = "Legs"; break;
        case DungeonData::ITEM_KNIFE:item = "Knife"; break;
        case DungeonData::ITEM_PICK: item = "Pick"; break;
    }

    if (item != "") {
        // Add the item to the inventory
        globals::inventory->addToInventory(item.c_str());

        // Remove the item from the world
        world[x + y * worldNumCols] = DungeonData::EMPTY;
    }
}

bool EntityPlayer::tryPickupAnimal(DungeonData::TileType tile)
{
    if (globals::currentAnimal)
    {
        // Player has animal, but not country
        if (!globals::currentCountry)
            globals::textbox->addText("You already have an animal ingredient, pick "
                "up another ingredient down below");

        // Player has animal and country
        else
            globals::textbox->addText("You already have both ingredients you "
                "need, try combining them");

        return false;
    }
    else
    {
        switch (tile) {
        case DungeonData::BAR_ANIMAL_RAVEN:
            globals::inventory->addToInventory("RavenDrink");
            globals::currentAnimal = globals::ANIMAL_RAVEN;
            break;
        case DungeonData::BAR_ANIMAL_WOLF:
            globals::inventory->addToInventory("WolfDrink");
            globals::currentAnimal = globals::ANIMAL_WOLF;
            break;
        case DungeonData::BAR_ANIMAL_TIGER:
            globals::inventory->addToInventory("TigerDrink");
            globals::currentAnimal = globals::ANIMAL_TIGER;
            break;
        case DungeonData::BAR_ANIMAL_HIPPO:
            globals::inventory->addToInventory("HippoDrink");
            globals::currentAnimal = globals::ANIMAL_HIPPO;
            break;
        case DungeonData::BAR_ANIMAL_WHALE:
            globals::inventory->addToInventory("WhaleDrink");
            globals::currentAnimal = globals::ANIMAL_WHALE;
            break;
        }

        globals::textbox->addText("You've picked up an ingredient!");
        Sound::getInstance()->pickUpItem("pickup");

    }

    return true;
}

bool EntityPlayer::tryPickupCountry(DungeonData::TileType tile)
{
    if (globals::currentCountry)
    {
        // Player has country, but not animal
        if (!globals::currentAnimal)
            globals::textbox->addText("You already have a national ingredient, pick "
                "up another ingredient from up above");

        // Player has animal and country
        else
            globals::textbox->addText("You already have both ingredients you "
                "need, try combining them");

        return false;
    }
    else
    {
        switch (tile) {
        case DungeonData::BAR_COUNTRY_IRE:
            globals::inventory->addToInventory("IREDrink");
            globals::currentCountry = globals::COUNTRY_IRE;
            break;
        case DungeonData::BAR_COUNTRY_SPA:
            globals::inventory->addToInventory("SPADrink");
            globals::currentCountry = globals::COUNTRY_SPA;
            break;
        case DungeonData::BAR_COUNTRY_ITA:
            globals::inventory->addToInventory("ITADrink");
            globals::currentCountry = globals::COUNTRY_ITA;
            break;
        case DungeonData::BAR_COUNTRY_POL:
            globals::inventory->addToInventory("POLDrink");
            globals::currentCountry = globals::COUNTRY_POL;
            break;
        case DungeonData::BAR_COUNTRY_RUS:
            globals::inventory->addToInventory("RUSDrink");
            globals::currentCountry = globals::COUNTRY_RUS;

            break;
        }

        globals::textbox->addText("You've picked up an ingredient!");
        Sound::getInstance()->pickUpItem("pickup");
    }

    return true;
}

void EntityPlayer::handleBarPuzzleLogic()
{
    if (globals::barPuzzleFinished)
    {
        globals::textbox->addText("Thirsty Guy Happy","Thirsty Guy", "Thanks for the drink, friend");
        return;
    }

    std::string animalString = "ERROR";
    switch (globals::currentAnimal)
    {
        case globals::ANIMAL_RAVEN: animalString = "Raven"; break;
        case globals::ANIMAL_WOLF: animalString = "Wolf"; break;
        case globals::ANIMAL_TIGER: animalString = "Tiger"; break;
        case globals::ANIMAL_HIPPO: animalString = "Hippo"; break;
        case globals::ANIMAL_WHALE: animalString = "Whale"; break;
    }

    std::string nationalityString = "ERROR";
    switch (globals::currentCountry)
    {
        case globals::COUNTRY_IRE: nationalityString = "Irish"; break;
        case globals::COUNTRY_SPA: nationalityString = "Spanish"; break;
        case globals::COUNTRY_ITA: nationalityString = "Italian"; break;
        case globals::COUNTRY_POL: nationalityString = "Polish"; break;
        case globals::COUNTRY_RUS: nationalityString = "Russian"; break;
    }

    std::string drinkString = nationalityString + " " + animalString;

    bool useAn = (globals::currentCountry == globals::COUNTRY_IRE
                  || globals::currentCountry == globals::COUNTRY_ITA);

    if (globals::currentCocktail) {

        if (globals::currentCocktail == globals::customerCocktail)
        {
            // Player has made the correct cocktail
            Sound::getInstance()->solvedPuzzle("solved");
            globals::textbox->addText("Thirsty Guy Happy", "Thirsty Guy", "Ahh, now that hits "
                "the spot. You sure make a good " + drinkString +
                ". Here, I'll open that door for you. Take whatever's "
                "behind it, you've earned it!");

            // Pull the lever
            int x, y;
            getLocation(DungeonData::BAR_CUSTOMER_LEVER_OFF, &x, &y);
            world[x + y * worldNumCols] = DungeonData::BAR_CUSTOMER_LEVER_ON;

            // Open the treasure door
            getLocation(DungeonData::BAR_TREASURE_DOOR_CLOSED, &x, &y);
            world[x + y * worldNumCols] = DungeonData::BAR_TREASURE_DOOR_OPEN;

            // Remove the cocktail from the player's inventory
            globals::inventory->removeFromInventory("Cocktail");

            // Set the completed flag to true
            globals::barPuzzleFinished = true;
        }
        else
        {
            int customerAnimal = globals::customerCocktail & 0B0000011111;
            int customerCountry = globals::customerCocktail & 0B1111100000;

            int playerAnimal = globals::currentAnimal;
            int playerCountry = globals::currentCountry;

            // Only animal is correct
            if (playerAnimal == customerAnimal && playerCountry != customerCountry) {
                std::string diffCountry = playerCountry < customerCountry ? "Eastern" : "Western";

                globals::textbox->addText("Thirsty Guy Half", "Thirsty Guy", (useAn ? "An " : "A ")
                    + drinkString + ", eh? Hmm, I like a good " + drinkString
                    + " as much as the next guy, but I'd prefer something a "
                      "little more `" + diffCountry + "`");
            }
            // Only country is correct
            else if (playerCountry == customerCountry && playerAnimal != customerAnimal)
            {
                std::string diffAnimal = playerAnimal < customerAnimal ? "Bigger" : "Smaller";
                globals::textbox->addText("Thirsty Guy Half", "Thirsty Guy",
                    (useAn ? "An " : "A ") + drinkString + ", eh? Hmm, I like "
                    "a good " + drinkString + " as much as the next guy, but "
                    "I'd prefer something a little `" + diffAnimal + "`");

            }
            // Nothing is correct
            else if (playerCountry != customerCountry && playerAnimal != customerAnimal)
            {
                std::string diffCountry = playerCountry < customerCountry ? "Eastern" : "Western";
                std::string diffAnimal = playerAnimal < customerAnimal ? "Bigger" : "Smaller";

                // Special case, to use 'wolves' instead of 'wolfs'
                std::string specialPlural = playerAnimal == globals::ANIMAL_WOLF ?
                            nationalityString + " Wolves"
                          : drinkString + "s";

                globals::textbox->addText("Thirsty Guy Angry","Thirsty Guy", (useAn ? "An " : "A ")
                    + drinkString +"?! Do I look like I drink " + specialPlural
                    + "?! No No No! This won't do at all! I'm looking for "
                    "something `" + diffAnimal + "` and more `" + diffCountry
                    + "`");
            }

            // Remove incorrect cockatil from inventory
            globals::inventory->removeFromInventory("Cocktail");
        }

        globals::currentAnimal = 0;
        globals::currentCountry = 0;
        globals::currentCocktail = 0;
    }
    else {
        // If player has only animal
        if (globals::currentAnimal && !globals::currentCountry) {
            globals::textbox->addText("Thirsty Guy", "Alright, now "
                "try grabbing another mixer from the shelf down below");
        }

        // If player has only country
        else if (!globals::currentAnimal && globals::currentCountry) {
            globals::textbox->addText("Thirsty Guy", "Alright, now "
                "try grabbing another mixer from the shelf up there");
        }

        // If player has both, but hasn't combined yet
        else if (globals::currentAnimal && globals::currentCountry) {
            globals::textbox->addText("Thirsty Guy", "Don't just "
                " stand there. Combine the ingredients, numbskull");
        }

        // If player has no mixer
        else {
            globals::textbox->addText("Thirsty Guy", "Hey, buddy. Fix "
                "me a drink, will ya. Ingredients should be in those "
                "shelves. I'm sure you know how to combine stuff, "
                "right?");
        }
    }
}

bool EntityPlayer::getLocation(DungeonData::TileType tile, int *x, int *y)
{
    for (int i = 0; i < worldNumCols; i++)
        for (int j = 0; j < worldNumRows; j++)
            if (world[i + j * worldNumCols] == tile) {
                *x = i;
                *y = j;
                return true;
            }
    return false;
}

bool EntityPlayer::tryTeleport(DungeonData::TileType tile)
{
    // Try to find the tile
    int x, y;
    if (getLocation(tile, &x, &y)) {
        // Teleport if found
        posX = (x + .5) * globals::CELL_SIZE;
        posY = (y + .5) * globals::CELL_SIZE;
        currentCol = x;
        currentRow = y;

        Sound::getInstance()->goThroughDoor("goThroughDoor");

        return true;
    }
    return false;
}

void EntityPlayer::handleFinalLever(DungeonData::TileType tile, int leverX, int leverY)
{
    switch (tile) {
    case DungeonData::FINAL_LEVER_A_OFF:
    case DungeonData::FINAL_LEVER_A_ON:
        // Toggle the door(s)
        toggleFinalDoor(DungeonData::FINAL_DOOR_A_CLOSED);
        toggleFinalDoor(DungeonData::FINAL_DOOR_C_CLOSED);

        // Toggle the lever
        world[leverX + leverY * worldNumCols] = tile == DungeonData::FINAL_LEVER_A_OFF
                ? DungeonData::FINAL_LEVER_A_ON
                : DungeonData::FINAL_LEVER_A_OFF;
        break;

    case DungeonData::FINAL_LEVER_B_OFF:
    case DungeonData::FINAL_LEVER_B_ON:
        // Toggle the door(s)
        toggleFinalDoor(DungeonData::FINAL_DOOR_A_CLOSED);
        toggleFinalDoor(DungeonData::FINAL_DOOR_E_CLOSED);

        // Toggle the lever
        world[leverX + leverY * worldNumCols] = tile == DungeonData::FINAL_LEVER_B_OFF
                ? DungeonData::FINAL_LEVER_B_ON
                : DungeonData::FINAL_LEVER_B_OFF;
        break;

    case DungeonData::FINAL_LEVER_C_OFF:
    case DungeonData::FINAL_LEVER_C_ON:
        // Toggle the door(s)
        toggleFinalDoor(DungeonData::FINAL_DOOR_C_CLOSED);
        toggleFinalDoor(DungeonData::FINAL_DOOR_E_CLOSED);
        toggleFinalDoor(DungeonData::FINAL_DOOR_F_CLOSED);

        // Toggle the lever
        world[leverX + leverY * worldNumCols] = tile == DungeonData::FINAL_LEVER_C_OFF
                ? DungeonData::FINAL_LEVER_C_ON
                : DungeonData::FINAL_LEVER_C_OFF;
        break;

    case DungeonData::FINAL_LEVER_D_OFF:
    case DungeonData::FINAL_LEVER_D_ON:
        // Toggle the door(s)
        toggleFinalDoor(DungeonData::FINAL_DOOR_B_CLOSED);
        toggleFinalDoor(DungeonData::FINAL_DOOR_D_CLOSED);
        toggleFinalDoor(DungeonData::FINAL_DOOR_C_CLOSED);

        // Toggle the lever
        world[leverX + leverY * worldNumCols] = tile == DungeonData::FINAL_LEVER_D_OFF
                ? DungeonData::FINAL_LEVER_D_ON
                : DungeonData::FINAL_LEVER_D_OFF;
        break;
    }
}

void EntityPlayer::toggleFinalDoor(DungeonData::TileType tile)
{
    // Note: Adding 6 to the closed door enum will give you the open version
    int fx, fy;

    // Search for closed door
    if (getLocation(tile, &fx, &fy))
        world[fx + fy * worldNumCols] = (DungeonData::TileType)(tile + 6);

    // Search for open door
    else if (getLocation((DungeonData::TileType)(tile + 6), &fx, &fy))
        world[fx + fy * worldNumCols] = tile;
}

void EntityPlayer::setMessage(std::string message)
{
    // Send the message in the format => id:message
    static int id = 0;
    this->message = std::to_string(id++) + ":" + message;
}
