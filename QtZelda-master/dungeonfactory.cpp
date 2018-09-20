#include "dungeonfactory.h"
#include "globals.h"
#include <string>
#include <iostream>
#include <sound.h>

// Initialize the instance to be null
DungeonFactory *DungeonFactory::instance = 0;

// Get the instance
DungeonFactory *DungeonFactory::getInstance() {
    if (instance == 0)
        instance = new DungeonFactory();
    return instance;
}

DungeonData *DungeonFactory::createDungeon(DungeonName name) {

    int w = globals::GRID_W;
    int h = globals::GRID_H;

    //DungeonData::TileType worldData[w * h];
    DungeonData::TileType *worldData =
            (DungeonData::TileType*) malloc(sizeof(DungeonData::TileType) * w * h);

    std::string bgFilename = "";

    switch (name) {
        case TEST:
            // Set up tile data
            // Make the ouside tiles walls
            for (int i = 0; i < w; i++) {
                for (int j = 0; j < h; j++) {
                    if (i == 0 || i == w-1 || j == 0 || j == h-1)
                        worldData[i + j * w] = DungeonData::WALL;
                    else
                        worldData[i + j * w] = DungeonData::EMPTY;
                }
            }
            // Add teleporters
            worldData[3 + 3 * w] = DungeonData::TELEPORTER_A;
            worldData[5 + 2 * w] = DungeonData::TELEPORTER_B;

            // Add mario
            worldData[7 + 2 * w] = DungeonData::MARIO_SPRITE;
            worldData[7 + 3 * w] = DungeonData::MARIO_TALK;

            // Set filename for background image
            bgFilename = ":dungeon_test.png";
            break;

    case INTRO:
        // Set up tile data
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                if (j <= 2 || j == 6)
                    worldData[i + j * w] = DungeonData::WALL;
                else
                    worldData[i + j * w] = DungeonData::EMPTY;
            }
        }

        // Add in more walls
        worldData[3 + 5 * w] = DungeonData::WALL;
        worldData[4 + 5 * w] = DungeonData::WALL;

        worldData[6 + 5 * w] = DungeonData::WALL;
        worldData[7 + 5 * w] = DungeonData::WALL;
        worldData[8 + 5 * w] = DungeonData::WALL;
        worldData[9 + 5 * w] = DungeonData::WALL;

        worldData[0 + 8 * w] = DungeonData::WALL;

        // Items
        worldData[7 + 7 * w] = DungeonData::ITEM_KNIFE;
        worldData[8 + 7 * w] = DungeonData::ITEM_PICK;

        // Add in lock stuff
        worldData[5 + 4 * w] = DungeonData::INTRO_HOLE;
        worldData[5 + 6 * w] = DungeonData::INTRO_LOCK_CLOSED;
        worldData[5 + 7 * w] = DungeonData::INTRO_LOCK_INTERACT;

        // NPC
        worldData[0 + 7 * w] = DungeonData::INTRO_NPC_SPRITE;
        worldData[1 + 7 * w] = DungeonData::INTRO_NPC_INTERACT;

        // Set filename for background image
        bgFilename = ":dungeon_intros.png";
        break;

    case TELEPORTERS:
        // Set up tile data
        // Add walls
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                if (i == 0 || i == w-1 || j == 0 || j == h-1
                        || i == 3 || i == 5 || i == 7 || i == 8)
                    worldData[i + j * w] = DungeonData::WALL;
                else
                    worldData[i + j * w] = DungeonData::EMPTY;
            }
        }
        // Clip vertical walls
        worldData[3 + 7 * w] = DungeonData::EMPTY;
        worldData[3 + 8 * w] = DungeonData::EMPTY;

        worldData[5 + 1 * w] = DungeonData::EMPTY;
        worldData[5 + 2 * w] = DungeonData::EMPTY;
        worldData[5 + 3 * w] = DungeonData::EMPTY;

        worldData[7 + 1 * w] = DungeonData::EMPTY;
        worldData[7 + 2 * w] = DungeonData::EMPTY;
        worldData[7 + 3 * w] = DungeonData::EMPTY;

        worldData[8 + 5 * w] = DungeonData::EMPTY;
        worldData[8 + 6 * w] = DungeonData::EMPTY;
        worldData[8 + 7 * w] = DungeonData::EMPTY;
        worldData[8 + 8 * w] = DungeonData::EMPTY;

        // Add horizontal walls
        worldData[1 + 6 * w] = DungeonData::WALL;
        worldData[2 + 6 * w] = DungeonData::WALL;

        worldData[4 + 4 * w] = DungeonData::WALL;
        worldData[6 + 4 * w] = DungeonData::WALL;
        worldData[7 + 4 * w] = DungeonData::WALL;

        worldData[9 + 3 * w] = DungeonData::WALL;
        worldData[10 + 3 * w] = DungeonData::WALL;

        // Add exit door
        worldData[0 + 5 * w] = DungeonData::TELEPORTERS_DOOR_EXIT;

        // Add teleporters
        // Start room
        worldData[2 + 2 * w] = DungeonData::TELEPORTER_1;
        worldData[2 + 4 * w] = DungeonData::TELEPORTER_4;

        // Room 1
        worldData[5 + 3 * w] = DungeonData::TELEPORTER_2;
        worldData[7 + 3 * w] = DungeonData::TELEPORTER_4;
        worldData[4 + 3 * w] = DungeonData::TELEPORTER_S;

        // Room 2
        worldData[4 + 5 * w] = DungeonData::TELEPORTER_3;
        worldData[4 + 7 * w] = DungeonData::TELEPORTER_4;
        worldData[1 + 8 * w] = DungeonData::TELEPORTER_S;

        // Room 3
        worldData[8 + 8 * w] = DungeonData::TELEPORTER_S;
        worldData[11 + 8 * w] = DungeonData::TELEPORTER_E;
        worldData[11 + 4 * w] = DungeonData::TELEPORTER_4;

        // Room 4
        worldData[6 + 8 * w] = DungeonData::TELEPORTER_S;

        // End Room
        worldData[9 + 2 * w] = DungeonData::TELEPORTER_S;

        // Add teleporter destinations
        worldData[1 + 5 * w] = DungeonData::TELEPORTER_S_DEST;
        worldData[4 + 2 * w] = DungeonData::TELEPORTER_1_DEST;
        worldData[1 + 7 * w] = DungeonData::TELEPORTER_2_DEST;
        worldData[8 + 6 * w] = DungeonData::TELEPORTER_3_DEST;
        worldData[6 + 5 * w] = DungeonData::TELEPORTER_4_DEST;
        worldData[10 + 2 * w] = DungeonData::TELEPORTER_E_DEST;

        // Add items
        worldData[10 + 1 * w] = DungeonData::ITEM_BODY;
        worldData[11 + 1 * w] = DungeonData::ITEM_HOOK;

        bgFilename = ":TeleporterRoom.png";
        break;

    case HUB:
        // Set up tile data
        // Add walls
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                if (i == 0 || i == w-1 || j == 0 || j == h-1)
                    worldData[i + j * w] = DungeonData::WALL;
                else
                    worldData[i + j * w] = DungeonData::EMPTY;
            }
        }

        // Add skelly seat stuff
        worldData[8 + 2 * w] = DungeonData::HUB_CHAIR_BEFORE;
        worldData[7 + 2 * w] = DungeonData::HUB_CHAIR_INTERACT;
        worldData[8 + 3 * w] = DungeonData::HUB_CHAIR_INTERACT_2;
        worldData[8 + 1 * w] = DungeonData::HUB_CONTROL_PANEL_OFF;

        // Add NPC
        worldData[9 + 1 * w] = DungeonData::HUB_NPC_SPRITE;
        worldData[9 + 2 * w] = DungeonData::HUB_NPC_INTERACT;
        worldData[10 + 1 * w] = DungeonData::CHASM_ANCHOR_BEFORE;

        // Add doors going to other puzzle rooms
        worldData[6 + 0 * w] = DungeonData::HUB_DOOR_N_CLOSED;
        worldData[6 + 9 * w] = DungeonData::HUB_DOOR_S;
        worldData[0 + 5 * w] = DungeonData::HUB_DOOR_W;
        worldData[12 + 5 * w] = DungeonData::HUB_DOOR_E;

        bgFilename = ":Room.png";
        break;

    case BAR:
        // Add walls
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                if (i == 0 || i == w-1 || j == 0 || j == h-1
                        || i == 4 || j == 1 || j == 8)
                    worldData[i + j * w] = DungeonData::WALL;
                else
                    worldData[i + j * w] = DungeonData::EMPTY;
            }
        }

        // Trim Walls
        worldData[1 + 1 * w] = DungeonData::EMPTY;
        worldData[2 + 1 * w] = DungeonData::EMPTY;
        worldData[3 + 1 * w] = DungeonData::EMPTY;
        worldData[4 + 1 * w] = DungeonData::EMPTY;
        worldData[5 + 1 * w] = DungeonData::EMPTY;

        worldData[5 + 8 * w] = DungeonData::EMPTY;

        // Add walls
        worldData[1 + 2 * w] = DungeonData::WALL;
        worldData[2 + 2 * w] = DungeonData::WALL;
        worldData[3 + 2 * w] = DungeonData::WALL;

        // Add ingredient shelves (note, order of ingredients are not
        // necessarily sorted in order of size, position on globe etc.)
        // Animals (top)
        worldData[7 + 2 * w] = DungeonData::BAR_ANIMAL_RAVEN;
        worldData[8 + 2 * w] = DungeonData::BAR_ANIMAL_HIPPO;
        worldData[9 + 2 * w] = DungeonData::BAR_ANIMAL_WHALE;
        worldData[10 + 2 * w] = DungeonData::BAR_ANIMAL_WOLF;
        worldData[11 + 2 * w] = DungeonData::BAR_ANIMAL_TIGER;

        // Countries (Bottom)
        worldData[7 + 7 * w] = DungeonData::BAR_COUNTRY_RUS;
        worldData[8 + 7 * w] = DungeonData::BAR_COUNTRY_SPA;
        worldData[9 + 7 * w] = DungeonData::BAR_COUNTRY_IRE;
        worldData[10 + 7 * w] = DungeonData::BAR_COUNTRY_POL;
        worldData[11 + 7 * w] = DungeonData::BAR_COUNTRY_ITA;

        // Add NPC
        worldData[3 + 4 * w] = DungeonData::BAR_CUSTOMER_SPRITE;
        worldData[5 + 4 * w] = DungeonData::BAR_CUSTOMER_TALK;

        // Add NPC's lever
        worldData[3 + 3 * w] = DungeonData::BAR_CUSTOMER_LEVER_OFF;

        // Add NPC's door
        worldData[4 + 1 * w] = DungeonData::BAR_TREASURE_DOOR_CLOSED;

        // Add exit door
        worldData[12 + 5 * w] = DungeonData::BAR_DOOR_EXIT;

        // Add items
        worldData[1 + 1 * w] = DungeonData::ITEM_LEGS;
        worldData[2 + 1 * w] = DungeonData::ITEM_ROPE;

        bgFilename = ":BarRoom.png";
        break;

    case CHASM:
        // Add walls
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                if (i == 0 || i == w-1 || j == 0 || j == h-1
                        || (j >= 3 && j <= 6))
                    worldData[i + j * w] = DungeonData::WALL;
                else
                    worldData[i + j * w] = DungeonData::EMPTY;
            }
        }

        // Add hook stuff
        worldData[2 + 1 * w] = DungeonData::CHASM_ANCHOR_BEFORE;
        worldData[2 + 2 * w] = DungeonData::CHASM_HOOK_SPOT;

        worldData[6 + 0 * w] = DungeonData::CHASM_DOOR_EXIT;
        worldData[6 + 9 * w] = DungeonData::CHASM_DOOR_NEXT;

        // Add man
        worldData[1 + 1 * w] = DungeonData::CHASM_MAN_SPRITE;
        worldData[1 + 2 * w] = DungeonData::CHASM_MAN_TALK;
        worldData[2 + 1 * w] = DungeonData::CHASM_ANCHOR_BEFORE;

        bgFilename = ":ChasmRoom.png";
        break;

    case FINAL:
        // Add walls
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                if (i == 0 || i == w-1 || j == 0 || j == h-1)
                    worldData[i + j * w] = DungeonData::WALL;
                else
                    worldData[i + j * w] = DungeonData::EMPTY;
            }
        }

        // Exit Door
        worldData[6 + 0 * w] = DungeonData::FINAL_DOOR_EXIT;

        // Items
        worldData[11 + 5 * w] = DungeonData::ITEM_HEAD;

        // 'Jutting out' walls
        for (int col = 4; col <= 11; ++col)
        {
            if (col <= 9)
            {
                worldData[col + 4 * w] = DungeonData::WALL;
                worldData[col + 6 * w] = DungeonData::WALL;
            }
            if (col >= 9)
            {
                worldData[col + 3 * w] = DungeonData::WALL;
                worldData[col + 7 * w] = DungeonData::WALL;
            }
        }

        // Levers
        worldData[4 + 3 * w] = DungeonData::FINAL_LEVER_A_OFF;
        worldData[5 + 3 * w] = DungeonData::FINAL_LEVER_B_OFF;
        worldData[6 + 3 * w] = DungeonData::FINAL_LEVER_C_OFF;
        worldData[7 + 3 * w] = DungeonData::FINAL_LEVER_D_OFF;

        // Doors
        worldData[4 + 5 * w] = DungeonData::FINAL_DOOR_A_CLOSED;
        worldData[5 + 5 * w] = DungeonData::FINAL_DOOR_B_CLOSED;
        worldData[6 + 5 * w] = DungeonData::FINAL_DOOR_C_CLOSED;
        worldData[7 + 5 * w] = DungeonData::FINAL_DOOR_D_CLOSED;
        worldData[8 + 5 * w] = DungeonData::FINAL_DOOR_E_CLOSED;
        worldData[9 + 5 * w] = DungeonData::FINAL_DOOR_F_CLOSED;

        bgFilename = ":LeverRoom.png";
        break;

    case TREASURE:
        // Add walls
        for (int i = 0; i < w; i++)
            for (int j = 0; j < h; j++)
                worldData[i + j * w] = DungeonData::WALL;

        // Hollow space
        for (int i = 5; i <= 7; ++i)
            for (int j = 5; j <= 8; ++j)
                worldData[i + j * w] = DungeonData::EMPTY;

        // Exit Door
        worldData[6 + 9 * w] = DungeonData::TREASURE_DOOR_EXIT;

        // Crown
        worldData[6 + 5 * w] = DungeonData::TREASURE_CROWN_INTERACT;

        bgFilename = ":FinalRoom.png";
        break;
    }

    return new DungeonData(bgFilename, worldData);
}

DungeonFactory::DungeonFactory()
{
}
