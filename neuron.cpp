#include "neuron.h"
#include <QGraphicsView>

neuron::neuron(int l, int n)
{
    value=rnd11();
    bias=rnd11()/5.0;
    type="Neuron";

    gridPos="L"+QString::number(l)+" N"+QString::number(n);
    this->setRect(-DOTSIZE/2,-DOTSIZE/2,DOTSIZE,DOTSIZE);
    this->setPos(20,20);


    effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);
    updateColor();


    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    //this->setZValue(1);

}
