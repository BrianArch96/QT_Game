#include "gameframe.h"

#include <QPainter>
#include <QRect>
#include <QColor>
#include <iostream>
#include <cstdlib>
#include <iostream>

#include "entityplayer.h"
#include "statedungeon.h"
#include "statecredits.h"
#include "dungeondata.h"
#include "dungeonfactory.h"
#include "input.h"
#include "globals.h"
#include <sound.h>

GameFrame::GameFrame()
{
    // Store a pointer to the GameEngine
    gameEngine = new GameEngine();

    /* Intro Room */
    // Set up tile data
    DungeonData *dIntroData =
            DungeonFactory::getInstance()->createDungeon(DungeonFactory::INTRO);
    StateDungeon *introDungeonState = new StateDungeon(dIntroData);

    // Set up player for the intro dungeon
    EntityPlayer *playerIntro = new EntityPlayer(8, 5);

    // Set up the player's world
    DungeonData::TileType *worldDataIntro;
    dIntroData->getData(&worldDataIntro, 0, 0);
    playerIntro->setWorld(worldDataIntro, 8, 10);

    // Add player to dungeon state
    introDungeonState->addEntity(playerIntro);

    /* Test Room */
    // Set up tile data
    DungeonData *dTestData =
            DungeonFactory::getInstance()->createDungeon(DungeonFactory::TEST);
    StateDungeon *testDungeonState = new StateDungeon(dTestData);

    // Set up player for the dungeon
    EntityPlayer *playerTest = new EntityPlayer(4, 4);

    // Set up the player's world
    DungeonData::TileType *worldDataTest;
    dTestData->getData(&worldDataTest, 0, 0);
    playerTest->setWorld(worldDataTest, 8, 10);

    // Add player to dungeon state
    testDungeonState->addEntity(playerTest);

    /* Teleporter Room */
    // Set up tile data
    DungeonData *dTeleporterData =
            DungeonFactory::getInstance()->createDungeon(DungeonFactory::TELEPORTERS);
    StateDungeon *teleporterDungeonState = new StateDungeon(dTeleporterData);

    // Set up player for the dungeon
    EntityPlayer *playerTeleporters = new EntityPlayer(5, 1);

    // Set up the player's world
    DungeonData::TileType *worldDataTeleporters;
    dTeleporterData->getData(&worldDataTeleporters, 0, 0);
    playerTeleporters->setWorld(worldDataTeleporters, 8, 10);

     // Add player to dungeon state
    teleporterDungeonState->addEntity(playerTeleporters);

    /* Hub Room */
    // Set up tile data
    DungeonData *dHubData =
            DungeonFactory::getInstance()->createDungeon(DungeonFactory::HUB);
    StateDungeon *hubDungeonState = new StateDungeon(dHubData);

    // Set up player for the dungeon
    EntityPlayer *playerHub = new EntityPlayer(6, 5);

    // Set up the player's world
    DungeonData::TileType *worldDataHub;
    dHubData->getData(&worldDataHub, 0, 0);
    playerHub->setWorld(worldDataHub, 8, 10);

     // Add player to dungeon state
    hubDungeonState->addEntity(playerHub);

    /* Bar Room */
    // Set up tile data
    DungeonData *dBarData =
            DungeonFactory::getInstance()->createDungeon(DungeonFactory::BAR);
    StateDungeon *barDungeonState = new StateDungeon(dBarData);

    // Set up player for the test dungeon
    EntityPlayer *playerBar = new EntityPlayer(5, 10);

    // Set up the player's world
    DungeonData::TileType *worldDataBar;
    dBarData->getData(&worldDataBar, 0, 0);
    playerBar->setWorld(worldDataBar, 8, 10);

     // Add player to dungeon state
    barDungeonState->addEntity(playerBar);

    /* Chasm Room */
    // Set up tile data
    DungeonData *dChasmData =
            DungeonFactory::getInstance()->createDungeon(DungeonFactory::CHASM);
    StateDungeon *chasmDungeonState = new StateDungeon(dChasmData);

    // Set up player for the test dungeon
    EntityPlayer *playerChasm = new EntityPlayer(1, 6);

    // Set up the player's world
    DungeonData::TileType *worldDataChasm;
    dChasmData->getData(&worldDataChasm, 0, 0);
    playerChasm->setWorld(worldDataChasm, 8, 10);

     // Add player to dungeon state
    chasmDungeonState->addEntity(playerChasm);

    /* Final Room */
    // Set up tile data
    DungeonData *dFinalData =
            DungeonFactory::getInstance()->createDungeon(DungeonFactory::FINAL);
    StateDungeon *finalDungeonState = new StateDungeon(dFinalData);

    // Set up player for the test dungeon
    EntityPlayer *playerFinal = new EntityPlayer(1, 6);

    // Set up the player's world
    DungeonData::TileType *worldDataFinal;
    dFinalData->getData(&worldDataFinal, 0, 0);
    playerFinal->setWorld(worldDataFinal, 8, 10);

     // Add player to dungeon state
    finalDungeonState->addEntity(playerFinal);

    /* Treasure Room */
    // Set up tile data
    DungeonData *dTreasureData =
            DungeonFactory::getInstance()->createDungeon(DungeonFactory::TREASURE);
    StateDungeon *treasureDungeonState = new StateDungeon(dTreasureData);

    // Set up player for the test dungeon
    EntityPlayer *playerTreasure = new EntityPlayer(8, 6);

    // Set up the player's world
    DungeonData::TileType *worldDataTreasure;
    dTreasureData->getData(&worldDataTreasure, 0, 0);
    playerTreasure->setWorld(worldDataTreasure, 8, 10);

     // Add player to dungeon state
    treasureDungeonState->addEntity(playerTreasure);

    /* Credits */
    StateCredits *stateCredits = new StateCredits();

    // Add dungeon states to game engine
    gameEngine->addGameState("intro", introDungeonState);
    gameEngine->addGameState("test", testDungeonState);
    gameEngine->addGameState("teleporters", teleporterDungeonState);
    gameEngine->addGameState("hub", hubDungeonState);
    gameEngine->addGameState("bar", barDungeonState);
    gameEngine->addGameState("chasm", chasmDungeonState);
    gameEngine->addGameState("final", finalDungeonState);
    gameEngine->addGameState("treasure", treasureDungeonState);
    gameEngine->addGameState("credits", stateCredits);

    Sound::getInstance()->playSound("music");
    gameEngine->changeGameState("intro");

    // Create a timer to update the game at 60 FPS
    timer.start(16, this);

    bg.setRgb(0, 0, 0);
}

// Drawing goes here
void GameFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);

    painter.fillRect(0, 0, width(), height(), bg);

    gameEngine->render(&painter);
}

// Update logic goes here
void GameFrame::timerEvent(QTimerEvent *event)
{
    gameEngine->tick();

    // Update input stuff
    Input::getInstance()->clearKeyJustPressed();

    update();
    repaint();
}
