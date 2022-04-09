#include <QGraphicsView>
#include "input.h"

input::input(int l, int p)
{
    value=rnd11();
    bias=0;//rnd11()/2.0;
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

void input::delVal()
{
    value=0;
}

