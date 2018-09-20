

#include "gametextbox.h"
#include "ui_gametextbox.h"
#include <iostream>
#include <QPainter>
#include <QColor>
#include <sound.h>
using namespace Qt;
//declare static map
std::map <std::string,QPixmap> GameTextbox::map;
GameTextbox::GameTextbox(QWidget *parent) :
    QFrame(parent),
    currentPixmap(0),
    ui(new Ui::GameTextbox)
{
    ui->setupUi(this);
    st = ui->textBrowser->verticalScrollBar();
    full = "";
}

QPixmap* GameTextbox::getImage(std::string name){

    if(map.empty()){
        //map["Brian"] = QPixmap(":vile-fluid.png");
       // map["Shane"] = QPixmap(":dragon-head.png");
        map["Thirsty Guy"] = QPixmap(":BarMan.png");
        map["Skelly"] = QPixmap(":SkellyTalking.png");
        map["Thirsty Guy Half"] = QPixmap(":BarManHalf.png");
        map["Thirsty Guy Angry"] = QPixmap(":BarManAngry.png");
        map["Thirsty Guy Happy"] = QPixmap(":happyBarMan.png");
        map["Chasm Guy Normal"] = QPixmap(":blueGuynormal.png");
        map["Chasm Guy Shocked"] = QPixmap(":blueGuyshocked.png");
        map["Skelly Talking"] = QPixmap(":SkellyTalking.png");
        map["Waluigi"] = QPixmap(":PurpleGuyNormal.png");
        map["Wario"] = QPixmap(":yellowGuyIcon.png");
    }
    if(map.find(name)!= map.end()){
        return &map[name];
    }


    return 0;
}

void GameTextbox::addText(std::string name, std::string text){
    this->addText(name, name, text);
    Sound::getInstance()->characterSpeak("speak");
    st->setValue(st->maximum());
}

void GameTextbox::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);
    QColor color;
    color.setRgb(10,20,30);
    int l,t;
    ui->gridLayout->getContentsMargins(&l,&t,0,0);
    if (currentPixmap != 0)
    {
        ui->gridLayout->setColumnStretch(0,1);
        ui->gridLayout->setColumnStretch(1,2);
        painter.drawPixmap(l,t,ui->frame->width(),ui->frame->height(),*currentPixmap);
    }
    else{
             ui->gridLayout->setColumnStretch(0,0);
             ui->gridLayout->setColumnStretch(1,1);
        }

    st->setValue(st->maximum());
}

void GameTextbox::addText(std::string imageName, std::string name, std::string text){
    std::string content = "\n<" + name + ">: " + text  + "\n";
    currentPixmap = GameTextbox::getImage(imageName);
    repaint();
    full += content;
    ui->textBrowser->setFont(QFont ("Courier", 9));
    ui->textBrowser->setText(full.c_str());
    st->setValue(st->maximum());
}


void GameTextbox::addText(std::string text){
    std::string content = "\n   " + text + "\n";
    currentPixmap = 0;
    repaint();
    full += content;
    ui->textBrowser->setFont(QFont ("Courier", 9));
    ui->textBrowser->setText(full.c_str());
    st->setValue(st->maximum());
}

void GameTextbox::hideImage()
{
    currentPixmap = 0;
    repaint();
}


GameTextbox::~GameTextbox()
{
    delete ui;
}
