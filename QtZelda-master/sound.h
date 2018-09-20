#ifndef SOUND_H
#define SOUND_H
#include <string>
#include <QMediaPlayer>
#include <map>
#include <QSound>

class Sound
{
public:
    static Sound* getInstance();
    void playSound(std::string);
    void playCharacterMoving(std::string);
    void pickUpItem(std::string);
    void goThroughDoor(std::string);
    void characterSpeak(std::string);
    void clickSomething(std::string);
    void solvedPuzzle(std::string);
    void skellySpeak(std::string);
    QUrl getSounds();
    void grapplingRock(std::string);

private:
    Sound();
    QMediaPlayer* playerSolved;
    QMediaPlayer* playerSkelly;
    QMediaPlayer* playerClickSomething;
    QMediaPlayer* playerGoThroughDoor;
    QMediaPlayer* playerCharacterSpeak;
    QMediaPlayer* player;
    QMediaPlayer* playerGrappling;
    QMediaPlayer *playerMoving;
    QMediaPlayer *playerPickUp;
    QMediaPlayer *playerTalk;
    static Sound* instance;
    std::map<std::string,std::string> sounds;


};

#endif // SOUND_H
