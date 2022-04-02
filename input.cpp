#include <QGraphicsView>
#include "input.h"

input::input(int l, int p)
{
    value=rnd11();
    bias=rnd11()/2.0;
    type="Input";

    gridPos="I"+QString::number(p);
    this->setRect(-DOTSIZE/2,-DOTSIZE/2,DOTSIZE,DOTSIZE);
    this->setPos(20,20);
    this->setBrush(Qt::blue);
    //this->setBoundingRegionGranularity(0.5);
    effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);
    updateColor();

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    //this->setZValue(1);
}

void input::focusInEvent(QFocusEvent *)
{
    updateInfoBox();
    emit object_selected(this);
}

void input::focusOutEvent(QFocusEvent *)
{
    //updateColor();
    //emit object_deselected(this);
}

void input::updateInfoBox()
{
    QString str_out="Type: \t"+type+"\nPosition: \t"+gridPos+"\n\n";

    str_out+="Bias: \t" + QString::number(bias)+"\n";
    str_out+="Value: \t" + QString::number(value)+"\n";
    str_out+="Output: \t" + QString::number(activFun(value))+"\n";

    emit setInfoTextUi(str_out);
}

