#include "input.h"
#include <iostream>

// Initialize the instance to be null
Input* Input::instance = 0;

// Get the instance
Input* Input::getInstance()
{
    // Initalize instance the first time
    if (instance == 0)
        instance = new Input();

    return instance;
}

Input::Input()
{
}

void Input::setKey(int key, bool pressed)
{
    keyStates[key] = pressed;
}

void Input::setKeyJustPressed(int key, bool pressed)
{
    keyJustPressedStates[key] = pressed;
}

void Input::clearKeyJustPressed()
{
    for (std::map<int, bool>::iterator it = keyJustPressedStates.begin();
         it != keyJustPressedStates.end();
         ++it)
    {
        keyJustPressedStates[it->first] = false;
    }
}

bool Input::getKey(int key)
{
    return keyStates[key];
}

bool Input::getKeyJustPressed(int key)
{
    return keyJustPressedStates[key];
}


