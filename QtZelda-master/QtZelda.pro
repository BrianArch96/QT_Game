#-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T13:42:19
#
#-------------------------------------------------

QT       += core gui \
         multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtZelda
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    rasterwindow.cpp \
    gameengine.cpp \
    gamestate.cpp \
    entity.cpp \
    gameframe.cpp \
    entityplayer.cpp \
    input.cpp \
    sprite.cpp \
    animation.cpp \
    statedungeon.cpp \
    dungeondata.cpp \
    textbox.cpp \
    gametextbox.cpp \
    banana.cpp \
    inventory.cpp \
    inventoryframe.cpp \
    itembutton.cpp \
    stateintro.cpp \
    dungeonfactory.cpp \
    sound.cpp \
    statecredits.cpp

HEADERS += \
        mainwindow.h \
    rasterwindow.h \
    gameengine.h \
    gamestate.h \
    entity.h \
    gameframe.h \
    entityplayer.h \
    input.h \
    globals.h \
    sprite.h \
    animation.h \
    statedungeon.h \
    dungeondata.h \
    textbox.h \
    gametextbox.h \
    banana.h \
    inventory.h \
    inventoryframe.h \
    itembutton.h \
    stateintro.h \
    dungeonfactory.h \
    sound.h \
    statecredits.h

FORMS += \
    mainwindow.ui \
    gametextbox.ui \
    inventoryframe.ui

RESOURCES += \
    qresources.qrc \
    sd.qrc \
    images.qrc
