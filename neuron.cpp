#include "neuron.h"
#include <QGraphicsView>

neuron::neuron()
{
    this->setRect(-DOTSIZE/2,-DOTSIZE/2,DOTSIZE,DOTSIZE);
    this->setPos(20,20);
    this->setBrush(Qt::blue);

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
