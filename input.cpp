#include <QGraphicsView>
#include "input.h"

input::input(int l, int p)
{
    gridPos="I"+QString::number(p);
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
    QString str_out="Type: \t"+type+"\nPosition: \t"+gridPos+"\n";
    QString str1="Value: \t" + QString::number(value)+"\n";

    emit setInfoTextUi(str_out+str1);
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
    return QPointF(x(),y());
}

void input::addVal(double val)
{
    value+=val;
}

QString input::getType(){
    return type;
}

QString input::getGridPos()
{
    return gridPos;
}
