#include "output.h"
#include <QGraphicsView>

output::output(int l, int p)
{
    gridPos="O"+QString::number(p);
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
    QString str_out="Type: \t"+type+"\nPosition: \t"+gridPos+"\n";
    QString str1="Value: \t" + QString::number(value)+"\n";

    emit setInfoTextUi(str_out+str1);
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

QString output::getType(){
    return type;
}

QString output::getGridPos()
{
    return gridPos;
}
