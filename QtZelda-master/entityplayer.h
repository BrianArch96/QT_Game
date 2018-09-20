#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include "entity.h"
#include <QPainter>
#include <QPixmap>
#include <cstring>
#include "dungeondata.h"

class EntityPlayer : public Entity
{
public:
    EntityPlayer(int x, int y);

    void setWorld(DungeonData::TileType *world, int rows, int cols);

    void render(QPainter *painter) override;
    void tick() override;
    EntityType getType() override;

    bool getMoving();
    void setCanMove(bool canMove);

    std::string getMessage();

private:
    QPixmap img;

    // An array containing world data, replace bool with other type later
    DungeonData::TileType *world;
    int worldNumCols, worldNumRows;

    int currentRow;
    int currentCol;

    int speed;

    bool moving;
    bool canMove;

    bool canMoveTo(int dx, int dy);
    void interact(int x, int y);

    // The player can set a message which can be read and interpreted by the
    // GameEngine, use this for changing scenes etc.
    std::string message;

    // Talk to skelly after he has been seated
    void talkToSkelly();

    // Move the player to the state(room) with the given name, specify the
    // player's rotation when he comes back
    void moveToState(std::string name, int rotation);

    // Try to pick up an item using identified by the given TileType
    bool tryPickupItem(DungeonData::TileType tile, int x, int y);

    // Get the location of the first tile of type 'tile' found, return false
    // if not found;
    bool getLocation(DungeonData::TileType tile, int *x, int *y);

    // Check for the first tile of type 'tile' and teleport to its position
    // if found
    bool tryTeleport(DungeonData::TileType tile);

    // Try picking up the ingredient associated with the given tile
    bool tryPickupAnimal(DungeonData::TileType tile);
    bool tryPickupCountry(DungeonData::TileType tile);

    // Handle bar puzzle logic
    void handleBarPuzzleLogic();

    // Handle logic when pulling lever in final puzzle
    void handleFinalLever(DungeonData::TileType tile, int leverX, int leverY);

    // Toggle the door in the final puzzle room with the given tiletype
    void toggleFinalDoor(DungeonData::TileType tile);

    // Set the player's message to be read by the gamestate
    void setMessage(std::string message);
};

#endif // ENTITYPLAYER_H
