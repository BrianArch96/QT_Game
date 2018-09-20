#include "textbox.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <string>
#include <QGraphicsTextItem>
#include <QTextBlockFormat>
#include <QTextCursor>
#include <QTextFormat>
#include <QFontMetrics>
#include <map>
#include <QPixmap>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::flush;
using std::cout;

textbox::textbox()
{
   view = new QGraphicsView();
   scene = new QGraphicsScene();
   view->setScene(scene);
   //view->setWindowFlags((Qt::Window | Qt::FramelessWindowHint));
  // pic.load(":Qtimage3.png");
  // pic1.load(":Qtimage2.png");
  // m["Brian"] = pic;
  // m["Glen"] = pic1;


}
/*textbox::textbox(string name, string message)
{
    this->name = name;
    this->message = message;
    view = new QGraphicsView();
    scene = new QGraphicsScene(0,0,300,50,view);
    view->setScene(scene);
    view->setWindowFlags((Qt::Window | Qt::FramelessWindowHint));
    QGraphicsTextItem* text =  scene->addText(QString::fromStdString(name));
    QGraphicsTextItem* text1 =  scene->addText(QString::fromStdString(message));

    text1->setPos(100,25);
    QFont newFont("Courier",8,QFont::Bold, true);

    // For centered text
    QFontMetrics fm(newFont);
    int w = fm.width(name.c_str());
    text->setFont(newFont);
    text->setPos(scene->width()/2 - w/2,-15);

    view->show();
}*/

/*textbox::textbox(string message){
    this->message = message;
}*/

void textbox::addText(string name, string message){
    QGraphicsTextItem* text =  scene->addText(QString::fromStdString(name));
    QGraphicsTextItem* text1 =  scene->addText(QString::fromStdString(message));

    text1->setPos(100,25);
    QFont newFont("Courier",8,QFont::Bold, true);

    // For centered text
    QFontMetrics fm(newFont);
    int widthName = fm.width(name.c_str());
    int widthMessage = fm.width(message.c_str());
    text->setFont(newFont);
    text->setPos(scene->width()/2 - widthName/2  ,0);
    text1->setFont(newFont);
    text1->setPos(scene->width()/2 - widthMessage/2  ,45);

   // view->show();
}

QGraphicsView* textbox::getView(){
    return view;
}

void textbox::addText(string message){
        QGraphicsTextItem* text =  scene->addText(QString::fromStdString(message));
        QFont newFont("Courier",8,QFont::Bold, true);
        QFontMetrics fm(newFont);

        int w = fm.width(message.c_str());
        text->setFont(newFont);
        text->setPos(scene->width()/2 - w/2,15);
      //  view->show();
    }



void textbox::drawImage(string name){
     QGraphicsPixmapItem* item = scene->addPixmap(m[name]);
     item->setPos(0,0);
     //view->show();
}

