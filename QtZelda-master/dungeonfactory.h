#ifndef DUNGEONFACTORY_H
#define DUNGEONFACTORY_H

#include "dungeondata.h"

class DungeonFactory
{
public:

    enum DungeonName {
        TEST,           // Test dungeon w/ two teleporters
        INTRO,          // Intro/Title screen w/ mini tutorial
        TELEPORTERS,    // Teleporter puzzle
        HUB,            // Central hub to go to each puzzle room
        BAR,            // Random drink puzzle
        CHASM,          // The room where you need to use the hooks
        FINAL,          // The final puzzle room
        TREASURE,       // The FINAL treasure room, congrats
    };

    static DungeonFactory *getInstance();

    DungeonData *createDungeon(DungeonName name);

private:
    // Private ctor to prevent instancing
    DungeonFactory();

    static DungeonFactory *instance;
};

#endif // DUNGEONFACTORY_H

