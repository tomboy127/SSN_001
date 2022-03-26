#include "neuron.h"
#include <QGraphicsView>

neuron::neuron(int l, int n)
{
    gridPos="L"+QString::number(l)+" N"+QString::number(n);
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
    QString str_out="Type: \t"+type+"\nPosition: \t"+gridPos+"\n";
    QString str1="Value: \t" + QString::number(value)+"\n";

    emit setInfoTextUi(str_out+str1);
}

void neuron::focusOutEvent(QFocusEvent *)
{
    effect->setOpacity(OPAC_NF);
    //emit setInfoTextUi("Select object");
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

QString neuron::getType(){
    return type;
}

QString neuron::getGridPos()
{
    return gridPos;
}
