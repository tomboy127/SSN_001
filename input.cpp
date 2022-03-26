#include <QGraphicsView>
#include "input.h"

input::input()
{
    this->setRect(-DOTSIZE/2,-DOTSIZE/2,DOTSIZE,DOTSIZE);
    this->setPos(20,20);
    this->setBrush(Qt::green);
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);
    effect->setOpacity(0.85);

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

double input::getVal()
{
    return value;
}

QPointF input::getPos()
{
    return QPointF(this->pos());
}

void input::addVal(double val)
{
    value+=val;
}
