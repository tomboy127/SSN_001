#include "output.h"
#include <QGraphicsView>

output::output()
{
    this->setRect(-DOTSIZE/2,-DOTSIZE/2,DOTSIZE,DOTSIZE);
    this->setPos(20,20);
    this->setBrush(Qt::red);
    effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);
    effect->setOpacity(OPAC_NF);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    //this->setZValue(1);

}

void output::del_obj()
{
    delete this;
}

void output::focusInEvent(QFocusEvent *)
{
    effect->setOpacity(OPAC_F);
}

void output::focusOutEvent(QFocusEvent *)
{
    effect->setOpacity(OPAC_NF);
}

double output::getVal()
{
    return value;
}

QPointF output::getPos()
{
    return QPointF(x(),y());
}

void output::addVal(double val)
{
    value+=val;
}
