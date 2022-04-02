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

void neuron::focusInEvent(QFocusEvent *)
{
    updateInfoBox();
}

void neuron::focusOutEvent(QFocusEvent *)
{
    //updateColor();
    //emit setInfoTextUi("Select object");
}

void neuron::updateInfoBox()
{
    QString str_out="Type: \t"+type+"\nPosition: \t"+gridPos+"\n\n";

    str_out+="Bias: \t" + QString::number(bias)+"\n";
    str_out+="Value: \t" + QString::number(value)+"\n";

    emit setInfoTextUi(str_out);
}


