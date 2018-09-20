#ifndef GAMETEXTBOX_H
#define GAMETEXTBOX_H

#include <QFrame>
#include <string>
#include <QScrollBar>
#include <QEvent>

namespace Ui {
class GameTextbox;
}

class GameTextbox : public QFrame
{
    Q_OBJECT

public:
    void addText(std::string text);
    void addText(std::string name, std::string text);
    void addText(std::string imageName, std::string name, std::string text);
    explicit GameTextbox(QWidget *parent = 0);

    void hideImage();

    ~GameTextbox();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap* currentPixmap;
    Ui::GameTextbox *ui;
    std::string full;
    static QPixmap* getImage(std::string name);
    QScrollBar *st;
    static std::map <std::string,QPixmap> map;
    QPixmap pic;
};

#endif // GAMETEXTBOX_H


