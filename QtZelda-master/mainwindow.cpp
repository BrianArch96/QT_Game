#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameframe.h"
#include "input.h"
#include "gametextbox.h"

#include <QGridLayout>
#include <iostream>
#include <map>
#include <QMediaPlayer>
#include "globals.h"
#include "inventoryframe.h"
#include <QSound>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GameTextbox *tb = new GameTextbox;

    ui->gridLayout->setRowStretch(1, 2);
    ui->gridLayout->setRowStretch(3, 1);
    ui->gridLayout->setColumnStretch(1, 2);
    ui->gridLayout->setColumnStretch(2, 2);

    ui->gridLayout->addWidget(new inventoryframe, 0, 0, 4, 1);   // Matthew's inventory goes here
    ui->gridLayout->addWidget(new GameFrame, 0, 1, 3, 2);   // Shane's game frame goes here
    ui->gridLayout->addWidget(tb, 3, 1, 1, 2);   // Brian's textbox goes here

    setWindowTitle("The legend of Ysolda");

    globals::textbox = tb;

    globals::textbox->addText("Welcome to the Legend of Ysolda! Use the WASD "
        "keys to move around, and the `E` key to interact with the environment. "
        "Try talking to that yellow guy over there");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);

    Input::getInstance()->setKey(event->key(), true);

    if (!event->isAutoRepeat())
        Input::getInstance()->setKeyJustPressed(event->key(), true);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    QMainWindow::keyReleaseEvent(event);

    Input::getInstance()->setKey(event->key(), false);
    Input::getInstance()->setKeyJustPressed(event->key(), false);

    std::cout << width() << ", " << height() << std::endl;
}
