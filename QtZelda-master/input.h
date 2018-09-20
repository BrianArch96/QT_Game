#ifndef INPUT_H
#define INPUT_H

#include <map>

class Input {

public:
    static Input* getInstance();

    void setKey(int key, bool pressed);
    void setKeyJustPressed(int key, bool pressed);

    void clearKeyJustPressed();

    bool getKey(int key);
    bool getKeyJustPressed(int key);


private:
    // private ctor to prevent instancing
    Input();

    static Input* instance;

    // Stores whether a key is being held
    std::map<int, bool> keyStates;

    // Stores whether the key has just been pressed this frame
    std::map<int, bool> keyJustPressedStates;
};

#endif // INPUT_H
