#include "output.h"
#include <QGraphicsView>

output::output(int l, int p)
{
    value=rnd11();
    bias=rnd11()/2.0;
    type="Output";

    gridPos="O"+QString::number(p);
    this->setRect(-DOTSIZE/2,-DOTSIZE/2,DOTSIZE,DOTSIZE);
    this->setPos(20,20);
    this->setBrush(Qt::red);
    effect = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect);
    updateColor();

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    //this->setZValue(1);

}
