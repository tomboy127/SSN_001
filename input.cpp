#include "input.h"
#include <QGraphicsView>

input::input()
{
    this->setRect(-DOTSIZE/2,-DOTSIZE/2,DOTSIZE,DOTSIZE);
    this->setPos(20,20);
    this->setBrush(Qt::green);

    setFlag(QGraphicsItem::ItemIsSelectable);
    //setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);



    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    //this->setFocus();

}

void input::del_obj()
{
    delete this;
}
