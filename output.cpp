#include "output.h"
#include <QGraphicsView>

output::output()
{
    this->setRect(-DOTSIZE/2,-DOTSIZE/2,DOTSIZE,DOTSIZE);
    this->setPos(20,20);
    this->setBrush(Qt::red);

    setFlag(QGraphicsItem::ItemIsSelectable);
    //setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);



    //this->setFlag(QGraphicsItem::ItemIsFocusable);
    //this->setFocus();
}

void output::del_obj()
{
    delete this;
}
