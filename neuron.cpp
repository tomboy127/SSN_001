#include "neuron.h"
#include <QGraphicsView>

neuron::neuron()
{
    this->setRect(-DOTSIZE/2,-DOTSIZE/2,DOTSIZE,DOTSIZE);
    this->setPos(20,20);
    this->setBrush(Qt::green);
    effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);
    effect->setOpacity(OPAC_NF);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    //this->setZValue(1);

}

void neuron::del_obj()
{
    delete this;
}

void neuron::focusInEvent(QFocusEvent *)
{
    effect->setOpacity(OPAC_F);
    QString str1="Val=" + QString::number(value)+"\n";
    QString str2="Val_2=" + QString::number(value*2)+"\n";

    emit setInfoTextUi(str1+str2);
}

void neuron::focusOutEvent(QFocusEvent *)
{
    effect->setOpacity(OPAC_NF);
    //setInfoTextUi(" ");
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
