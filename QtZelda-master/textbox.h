#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <QGraphicsScene>
#include <string>
#include <iostream>
#include <map>
#include <QPixmap>
using namespace std;


class textbox
{
public:
    textbox();
    void addText(string name, string message);
    void addText(string message);
    void drawImage(string name);
    string slow_print(string message);
    QGraphicsView* getView();
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    map <string,QPixmap> m;
    QPixmap pic;
    QPixmap pic1;

};

#endif // TEXTBOX_H
