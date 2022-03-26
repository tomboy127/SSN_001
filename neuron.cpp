#include "neuron.h"
#include <QGraphicsView>

neuron::neuron()
{
    this->setRect(-DOTSIZE/2,-DOTSIZE/2,DOTSIZE,DOTSIZE);
    this->setPos(20,20);
    this->setBrush(Qt::blue);
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);
    effect->setOpacity(0.85);

    setFlag(QGraphicsItem::ItemIsSelectable);
    //setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);




    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    //this->setFocus();

}

void neuron::del_obj()
{
    delete this;
}

double neuron::getVal()
{
   return value;
}

QPointF neuron::getPos()
{
    return QPointF(x(),y());
}

void neuron::addVal(double val)
{
    value+=val;
}
