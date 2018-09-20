#include "gameengine.h"
#include "globals.h"
#include <iostream>

GameEngine::GameEngine()
    : consumedMessageId(-1),
      blackValue(0),
      fadeDirection(0)
{
    gameStates = initMap();
}

// Render the game, called at a rate of 60 FPS
void GameEngine::render(QPainter *painter)
{
    currentState->render(painter);

    QColor c(0, 0, 0, (int)(blackValue * 255));
    painter->fillRect(0, 0, painter->window().width(), painter->window().height(), c);
}

// Update the game, called at a rate of 60 FPS
void GameEngine::tick()
{
    // Handle messages from current gamestate first
    std::string message = currentState->getMessage();

    // First check if the message is not empty
    if (message.compare("") != 0)
    {
        // Split the message into id and message
        int messageId = std::stoi(message.substr(0, message.find(":")));
        message = message.substr(message.find(":") + 1);

        // Check if message has already been processed
        if (messageId > consumedMessageId)
        {
            // Change game state if requested
            if (message.compare(0, 11, "changestate") == 0)
            {
                changeGameState(message.substr(12));
            }
            // Fade the game to black
            else if (message.compare("fadeend") == 0)
            {
                fadeDirection = 1;
            }

            // Update the most recently consumed message
            consumedMessageId = messageId;
        }
    }

    if (fadeDirection == 0)
        // Update the current state
        currentState->tick();

    else
    {
        // Fade to creditss

        blackValue += globals::FADE_SPEED * fadeDirection;

        // Cap at 1 max and switch direction
        if (fadeDirection == 1 && blackValue >= 1)
        {
            changeGameState("credits");
            fadeDirection = -1;
            blackValue = 1;
        }
        // Cap at 0 min
        else if (fadeDirection == -1 && blackValue <= 0)
        {
            blackValue = 0;
            fadeDirection = 0;
        }
    }
}

// Add a GameState to this GameEngine
void GameEngine::addGameState(std::string name, GameState *state)
{
    gameStates[name] = state;
}

// Go to the GameState with the given name
void GameEngine::changeGameState(std::string name)
{
    currentState = gameStates[name];
}

// Helper function to initialize the map
std::map<std::string, GameState*> GameEngine::initMap()
{
    std::map<std::string, GameState *> m;
    return m;
}
