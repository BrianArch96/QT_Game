#include "dungeondata.h"
#include "globals.h"
#include <iostream>

// Define the static map
std::map<DungeonData::TileType, QPixmap*> DungeonData::tileSprites;

DungeonData::DungeonData()
    : bg(new QPixmap),
      gridData(0),
      gridW(0), gridH(0)
{
}

DungeonData::DungeonData(std::string fileName, DungeonData::TileType *gridData)
    : bg(new QPixmap),
      gridData(gridData),
      gridW(globals::GRID_W), gridH(globals::GRID_H)
{
    bg->load(fileName.c_str());
}

DungeonData::~DungeonData()
{
    delete bg;
}

QPixmap *DungeonData::getBg()
{
    return bg;
}

void DungeonData::getData(TileType **gridData, int *w, int *h)
{
    *gridData = this->gridData;

    if (w != 0) *w = gridW;
    if (h != 0) *h = gridH;
}

QPixmap *DungeonData::getTileTexture(TileType tileType)
{
    // Intialize the map first time around
    if (tileSprites.empty()) {

        // Intro room
        tileSprites[LEVER_A_OFF] = new QPixmap(":SwitchOff.png");
        tileSprites[LEVER_A_ON] = new QPixmap(":SwitchOn.png");
        tileSprites[DOOR_A_CLOSED] = new QPixmap(":DoorClosed.png");
        tileSprites[DOOR_A_OPEN] = new QPixmap(":DoorOpen.png");

        tileSprites[INTRO_LOCK_CLOSED] = new QPixmap(":LockedDoor.png");
        tileSprites[INTRO_LOCK_OPEN] = new QPixmap(":UnlockedDoor.png");

        tileSprites[INTRO_NPC_SPRITE] = new QPixmap(":yellowMario.png");

        // Hub room
        tileSprites[HUB_DOOR_N_CLOSED] = tileSprites[DOOR_A_CLOSED];
        tileSprites[HUB_DOOR_N_OPEN] = tileSprites[DOOR_A_OPEN];
        tileSprites[HUB_DOOR_S] = tileSprites[DOOR_A_OPEN];
        tileSprites[HUB_DOOR_E] = tileSprites[DOOR_A_OPEN];
        tileSprites[HUB_DOOR_W] = tileSprites[DOOR_A_OPEN];
        tileSprites[HUB_CHAIR_BEFORE] = new QPixmap(":Pillow.png");
        tileSprites[HUB_CHAIR_AFTER] = new QPixmap(":PillowWithSkelly.png");
        tileSprites[HUB_CONTROL_PANEL_OFF] = new QPixmap(":ControlPanel.png");
        tileSprites[HUB_CONTROL_PANEL_ON] = new QPixmap(":ControlPanelLit.png");
        tileSprites[HUB_NPC_SPRITE] = new QPixmap(":purpleGuy.png");

        // Teleporter puzzle room
        tileSprites[TELEPORTERS_DOOR_EXIT] = tileSprites[DOOR_A_OPEN];
        tileSprites[TELEPORTER_S] = new QPixmap(":TeleporterRed.png");
        tileSprites[TELEPORTER_1] = new QPixmap(":TeleporterBlue.png");
        tileSprites[TELEPORTER_2] = tileSprites[TELEPORTER_1];
        tileSprites[TELEPORTER_3] = tileSprites[TELEPORTER_1];
        tileSprites[TELEPORTER_4] = tileSprites[TELEPORTER_1];
        tileSprites[TELEPORTER_E] = tileSprites[TELEPORTER_1];
        tileSprites[TELEPORTER_S_HIDDEN] = tileSprites[TELEPORTER_1];

        // Test room
        tileSprites[TELEPORTER_A] = tileSprites[TELEPORTER_1];
        tileSprites[TELEPORTER_B] = tileSprites[TELEPORTER_S];
        tileSprites[MARIO_SPRITE] = new QPixmap(":MarioSprite.png");

        // Bar room
        tileSprites[BAR_CUSTOMER_SPRITE] = tileSprites[MARIO_SPRITE];
        tileSprites[BAR_CUSTOMER_LEVER_OFF] = tileSprites[LEVER_A_OFF];
        tileSprites[BAR_CUSTOMER_LEVER_ON] = tileSprites[LEVER_A_ON];
        tileSprites[BAR_TREASURE_DOOR_CLOSED] = new QPixmap("BarDoor.png");
        tileSprites[BAR_TREASURE_DOOR_OPEN] = new QPixmap("BarDoorOpen.png");
        tileSprites[BAR_DOOR_EXIT] = tileSprites[DOOR_A_OPEN];

        // Chasm room
        tileSprites[CHASM_DOOR_EXIT] = tileSprites[DOOR_A_OPEN];
        tileSprites[CHASM_DOOR_NEXT] = tileSprites[DOOR_A_OPEN];
        tileSprites[CHASM_ANCHOR_BEFORE] = new QPixmap(":Rock.png");
        tileSprites[CHASM_ANCHOR_AFTER] = new QPixmap(":RopeRock.png");
        tileSprites[CHASM_ROPE] = new QPixmap(":RopeWalk.png");
        tileSprites[CHASM_TARGET_WALL_EXTENDED] = new QPixmap(":RopeHit1.png");
        tileSprites[CHASM_TARGET_WALL] = new QPixmap(":RopeHit2.png");
        tileSprites[CHASM_MAN_SPRITE] = new QPixmap(":blueMario.png");

        // Final room
        // Levers
        tileSprites[FINAL_LEVER_A_OFF] = tileSprites[LEVER_A_OFF];
        tileSprites[FINAL_LEVER_B_OFF] = tileSprites[LEVER_A_OFF];
        tileSprites[FINAL_LEVER_C_OFF] = tileSprites[LEVER_A_OFF];
        tileSprites[FINAL_LEVER_D_OFF] = tileSprites[LEVER_A_OFF];
        tileSprites[FINAL_LEVER_A_ON] = tileSprites[LEVER_A_ON];
        tileSprites[FINAL_LEVER_B_ON] = tileSprites[LEVER_A_ON];
        tileSprites[FINAL_LEVER_C_ON] = tileSprites[LEVER_A_ON];
        tileSprites[FINAL_LEVER_D_ON] = tileSprites[LEVER_A_ON];

        // Doors
        tileSprites[FINAL_DOOR_EXIT] = tileSprites[DOOR_A_OPEN];
        tileSprites[FINAL_DOOR_A_CLOSED] = tileSprites[BAR_TREASURE_DOOR_CLOSED];
        tileSprites[FINAL_DOOR_B_CLOSED] = tileSprites[BAR_TREASURE_DOOR_CLOSED];
        tileSprites[FINAL_DOOR_C_CLOSED] = tileSprites[BAR_TREASURE_DOOR_CLOSED];
        tileSprites[FINAL_DOOR_D_CLOSED] = tileSprites[BAR_TREASURE_DOOR_CLOSED];
        tileSprites[FINAL_DOOR_E_CLOSED] = tileSprites[BAR_TREASURE_DOOR_CLOSED];
        tileSprites[FINAL_DOOR_F_CLOSED] = tileSprites[BAR_TREASURE_DOOR_CLOSED];
        tileSprites[FINAL_DOOR_A_OPEN] = tileSprites[BAR_TREASURE_DOOR_OPEN];
        tileSprites[FINAL_DOOR_B_OPEN] = tileSprites[BAR_TREASURE_DOOR_OPEN];
        tileSprites[FINAL_DOOR_C_OPEN] = tileSprites[BAR_TREASURE_DOOR_OPEN];
        tileSprites[FINAL_DOOR_D_OPEN] = tileSprites[BAR_TREASURE_DOOR_OPEN];
        tileSprites[FINAL_DOOR_E_OPEN] = tileSprites[BAR_TREASURE_DOOR_OPEN];
        tileSprites[FINAL_DOOR_F_OPEN] = tileSprites[BAR_TREASURE_DOOR_OPEN];

        // Treasure room
        tileSprites[TREASURE_DOOR_EXIT] = tileSprites[DOOR_A_OPEN];
        tileSprites[TREASURE_CROWN_INTERACT] = new QPixmap(":Crown.png");

        // Items
        tileSprites[ITEM_HOOK] = new QPixmap(":Hook.png");
        tileSprites[ITEM_ROPE] = new QPixmap(":Rope.png");
        tileSprites[ITEM_HEAD] = new QPixmap(":Head.png");
        tileSprites[ITEM_BODY] = new QPixmap(":Body.png");
        tileSprites[ITEM_LEGS] = new QPixmap(":Legs.png");
        tileSprites[ITEM_KNIFE] = new QPixmap(":Knife.png");
        tileSprites[ITEM_PICK] = new QPixmap(":Pick.png");
    }

    // Return a pointer to the image
    if (tileSprites.find(tileType) != tileSprites.end())
        return tileSprites[tileType];

    // If there is no image for the given tile, return a null pointer
    return 0;
}

bool DungeonData::getSolid(TileType tileType)
{
    return tileType == WALL
            || tileType == MARIO_SPRITE
            || tileType == DOOR_A_CLOSED
            || tileType == BAR_TREASURE_DOOR_CLOSED
            || tileType == CHASM_MAN_SPRITE
            || tileType == CHASM_ANCHOR_BEFORE
            || tileType == CHASM_ANCHOR_AFTER
            || tileType == CHASM_TARGET_WALL
            || tileType == HUB_CHAIR_AFTER
            || tileType == HUB_NPC_SPRITE
            || tileType == HUB_CONTROL_PANEL_OFF
            || tileType == HUB_CONTROL_PANEL_ON
            || tileType == HUB_DOOR_N_CLOSED
            || tileType == FINAL_DOOR_A_CLOSED
            || tileType == FINAL_DOOR_B_CLOSED
            || tileType == FINAL_DOOR_C_CLOSED
            || tileType == FINAL_DOOR_D_CLOSED
            || tileType == FINAL_DOOR_E_CLOSED
            || tileType == FINAL_DOOR_F_CLOSED
            || tileType == INTRO_LOCK_CLOSED
            || tileType == INTRO_NPC_SPRITE
            ;
}
