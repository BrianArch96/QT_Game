#include "sound.h"
#include <iostream>
#include <qmediaplaylist.h>

Sound* Sound::instance = 0;


Sound* Sound::getInstance(){
    if (instance == 0){
        instance = new Sound();

    }
    return instance;
}

Sound::Sound(){
    player = new QMediaPlayer();
    playerSkelly = NULL;
    playerMoving = NULL;
    playerPickUp = NULL;
    playerGrappling = NULL;
    playerSolved = NULL;
    playerClickSomething = NULL;
    playerGoThroughDoor = NULL;
    playerCharacterSpeak = NULL;
    sounds["solved"] = "qrc:/solved.mp3";
    sounds["music"] = "qrc:/music.mp3";
    sounds["walking"] = "qrc:/moving.mp3";
    sounds["pickup"] = "qrc:/pickup.mp3";
    sounds["goThroughDoor"] = "qrc:/doors.mp3";
    sounds["speak"] = "qrc:/speak.mp3";
    sounds["click"] = "qrc:/click.mp3";
    sounds["grappling"] = "qrc:/grappling.mp3";
    sounds["skelly"] = "qrc:/skelly.mp3";
    sounds["grappling"] = "qrc:/grappling.mp3";
}
void Sound::solvedPuzzle(std::string name){
    if (playerSolved == NULL){
        playerSolved = new QMediaPlayer;
        playerSolved->setMedia(QUrl(sounds[name].c_str()));
        playerSolved->setVolume(50);
    }
    playerSolved->play();
}

void Sound::grapplingRock(std::string name){
    if (playerGrappling == NULL){
        playerGrappling = new QMediaPlayer;
        playerGrappling->setMedia(QUrl(sounds[name].c_str()));
        playerGrappling->setVolume(50);
    }
       playerGrappling->play();
}

void Sound::skellySpeak(std::string name){
    if (playerSkelly == NULL){
        playerSkelly = new QMediaPlayer();
        playerSkelly->setMedia(QUrl(sounds[name].c_str()));
        playerSkelly->setVolume(50);

    }
     playerSkelly->play();
}

void Sound::goThroughDoor(std::string name){
    if (playerGoThroughDoor == NULL){
    playerGoThroughDoor = new QMediaPlayer();
    playerGoThroughDoor->setMedia(QUrl(sounds[name].c_str()));
    playerGoThroughDoor->setVolume(50);

    }
     playerGoThroughDoor->play();

}
void Sound::clickSomething(std::string name){
    if(playerClickSomething == NULL){
        playerClickSomething = new QMediaPlayer();
        playerClickSomething->setMedia(QUrl(sounds[name].c_str()));
        playerClickSomething->setVolume(50);


    }
    playerClickSomething->play();
}

void Sound::characterSpeak(std::string name){
    if (playerCharacterSpeak == NULL){
        playerCharacterSpeak = new QMediaPlayer();
        playerCharacterSpeak->setMedia(QUrl(sounds[name].c_str()));
        playerCharacterSpeak->setVolume(50);

    }
    playerCharacterSpeak->play();
}

void Sound::playSound(std::string name){
   QMediaPlaylist* playlist = new QMediaPlaylist();
   playlist->addMedia(QUrl(sounds[name].c_str()));
   playlist->setPlaybackMode(QMediaPlaylist::Loop);
   player->setPlaylist(playlist);
   player->setVolume(20);
   player->play();
}

void Sound::pickUpItem(std::string name){
    if(playerPickUp == NULL) {
        playerPickUp = new QMediaPlayer();
        playerPickUp->setMedia(QUrl(sounds[name].c_str()));
        playerPickUp->setVolume(50);

    }
    playerPickUp->play();
}

void Sound::playCharacterMoving(std::string name){
    if(playerMoving == NULL){
        playerMoving = new QMediaPlayer();
        playerMoving->setMedia(QUrl(sounds[name].c_str()));
        playerMoving->setVolume(60);

    }
    playerMoving->play();
}
