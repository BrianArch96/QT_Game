#ifndef DUNGEONDATA_H
#define DUNGEONDATA_H

#include <QPixmap>
#include <string>
#include <map>

class DungeonData
{
public:
    enum TileType {
        /* Common tiles */
        EMPTY,          // Player can move into it
        WALL,           // Player cannot move into it

        /* Item tiles */
        ITEM_HEAD,      // The skeleton's head
        ITEM_BODY,      // The skeleton's torso
        ITEM_LEGS,      // The skeleton's legs
        ITEM_HOOK,      // Part of the Grappling Hook
        ITEM_ROPE,      // Part of the Grappling Hook
        ITEM_KNIFE,     // Part of lockpick
        ITEM_PICK,      // Part of lockpick

        /* Test room */
        TELEPORTER_A,   // Will teleport the player to B
        TELEPORTER_B,   // Will teleport the player to A
        MARIO_SPRITE,   // The tile where mario's sprite is
        MARIO_TALK,     // Stand on this tile to talk to mario

        /* Intro room */
        LEVER_A_OFF,    // Will open door A
        LEVER_A_ON,     // Lever A after being opened
        DOOR_A_CLOSED,  // Will be opened by lever A
        DOOR_A_OPEN,    // Will transport player to test room

        INTRO_LOCK_CLOSED,      // Sprite for lock
        INTRO_LOCK_OPEN,        // "
        INTRO_LOCK_INTERACT,    // Stand here to interact with lock
        INTRO_HOLE,             // Hole to go to dungeon

        INTRO_NPC_SPRITE,       // The sprite for the town npc
        INTRO_NPC_INTERACT,     // Stand here to interact with him

        /* Hub room */
        HUB_DOOR_N_CLOSED,  // Closed until opened by Skelly
        HUB_DOOR_N_OPEN,    // Transports player to Treasure room
        HUB_DOOR_S,         // " to Chasm Room
        HUB_DOOR_E,         // " to Teleporter Room
        HUB_DOOR_W,         // " to Bar Room
        HUB_CHAIR_INTERACT,     // Talk to skelly here (LEFT)
        HUB_CHAIR_INTERACT_2,   // Talk to skelly here (DOWN)
        HUB_CHAIR_BEFORE,   // Put Skelly on this chair
        HUB_CHAIR_AFTER,    // The chair sprite after skelly has been seated
        HUB_CONTROL_PANEL_OFF,  // Skelly's control panel
        HUB_CONTROL_PANEL_ON,   // "
        HUB_NPC_SPRITE,         // Hub guy's sprite
        HUB_NPC_INTERACT,       // Stand here to talk to him. or talk to skelly (RIGHT)

        /* Teleporter puzzle room */
        TELEPORTERS_DOOR_EXIT,  // To exit the teleporter room

        // Teleporters for puzzle
        TELEPORTER_1,   // Go to room 1
        TELEPORTER_2,   // " room 2
        TELEPORTER_3,   // " room 3
        TELEPORTER_4,   // " room 4
        TELEPORTER_E,   // " end room
        TELEPORTER_S,   // " starting room
        TELEPORTER_S_HIDDEN,    // same as above, but looks like a normal teleporter

        // Destinations of teleporters
        TELEPORTER_1_DEST,  // The destination of teleporter to room 1
        TELEPORTER_2_DEST,  // " room 2
        TELEPORTER_3_DEST,  // " room 3
        TELEPORTER_4_DEST,  // " room 4
        TELEPORTER_E_DEST,  // " end room
        TELEPORTER_S_DEST,  // " starting room

        /* Bar room */
        // The customer
        BAR_CUSTOMER_SPRITE,    // The sprite
        BAR_CUSTOMER_TALK,      // Stand on this tile to talk to the customer

        // The customer's lever
        BAR_CUSTOMER_LEVER_OFF,
        BAR_CUSTOMER_LEVER_ON,

        // The door which the customer will open
        BAR_TREASURE_DOOR_CLOSED,
        BAR_TREASURE_DOOR_OPEN,

        BAR_DOOR_EXIT,  // To exit the bar room

        // Tiles to stand on to get ingredients
        // Animals
        BAR_ANIMAL_RAVEN,
        BAR_ANIMAL_WOLF,
        BAR_ANIMAL_TIGER,
        BAR_ANIMAL_HIPPO,
        BAR_ANIMAL_WHALE,
        // Countries
        BAR_COUNTRY_IRE,
        BAR_COUNTRY_SPA,
        BAR_COUNTRY_ITA,
        BAR_COUNTRY_POL,
        BAR_COUNTRY_RUS,

        /* Chasm Room */
        CHASM_HOOK_SPOT,            // Stand here to shoot the grappling hook
        CHASM_ROPE,                 // Rope which you can stand on
        CHASM_ANCHOR_BEFORE,        // The anchor stone before grappling hook
        CHASM_ANCHOR_AFTER,         // The anchor stone after grappling hook
        CHASM_TARGET_WALL,          // The wall after being shot with hook
        CHASM_TARGET_WALL_EXTENDED, // The tile just before the wall

        CHASM_DOOR_EXIT,        // The door back to the hub
        CHASM_DOOR_NEXT,        // The door to the treasure room

        CHASM_MAN_SPRITE,       // Sprite for the man in the chasm
        CHASM_MAN_TALK,         // Stand here to talk to the man

        /* Final Room */
        FINAL_DOOR_EXIT,        // To exit the final room

        // Levers
        FINAL_LEVER_A_OFF,
        FINAL_LEVER_B_OFF,
        FINAL_LEVER_C_OFF,
        FINAL_LEVER_D_OFF,
        FINAL_LEVER_A_ON,
        FINAL_LEVER_B_ON,
        FINAL_LEVER_C_ON,
        FINAL_LEVER_D_ON,

        // Doors
        FINAL_DOOR_A_CLOSED,
        FINAL_DOOR_B_CLOSED,
        FINAL_DOOR_C_CLOSED,
        FINAL_DOOR_D_CLOSED,
        FINAL_DOOR_E_CLOSED,
        FINAL_DOOR_F_CLOSED,
        FINAL_DOOR_A_OPEN,
        FINAL_DOOR_B_OPEN,
        FINAL_DOOR_C_OPEN,
        FINAL_DOOR_D_OPEN,
        FINAL_DOOR_E_OPEN,
        FINAL_DOOR_F_OPEN,

        /* Treasure Room */
        TREASURE_DOOR_EXIT,     // To leave the treasure room

        TREASURE_CROWN_INTERACT,
    };

    // A mapping of tiles to their respective sprites, used for dynamically
    // changing tiles like levers, doors etc.
    static std::map<TileType, QPixmap*> tileSprites;

    static QPixmap *getTileTexture(TileType tileType);

    // Return true if the tile cannot be walked into
    static bool getSolid(TileType tileType);

    DungeonData();
    DungeonData(std::string fileName, TileType *gridData);
    ~DungeonData();

    QPixmap *getBg();
    void getData(TileType **gridData, int *w, int *h);

private:
    QPixmap *bg;

    int gridW;
    int gridH;
    TileType *gridData;
};

#endif // DUNGEONDATA_H
