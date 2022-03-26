#include <QGraphicsView>
#include "input.h"

input::input()
{
    this->setRect(-DOTSIZE/2,-DOTSIZE/2,DOTSIZE,DOTSIZE);
    this->setPos(20,20);
    this->setBrush(Qt::blue);
    effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);
    effect->setOpacity(OPAC_NF);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    //this->setZValue(1);
}

void input::del_obj()
{
    delete this;
}

void input::focusInEvent(QFocusEvent *)
{
    effect->setOpacity(OPAC_F);
    QString str1="Vald=" + QString::number(value)+"\n";
    QString str2="Vald_2=" + QString::number(value*2)+"\n";

    emit setInfoTextUi(str1+str2);
}

void input::focusOutEvent(QFocusEvent *)
{
    effect->setOpacity(OPAC_NF);
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
