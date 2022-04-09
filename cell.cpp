#include "cell.h"

double cell::activFun(double val)
{
    double val_out;

    if(val>1) val_out=1;
    else if(val<-1) val_out=-1;
    else val_out=val;

    //if(val>=0) val_out=val;
    //if(val>1) val_out=1;
    //if(val<0) val_out=0;

    return val_out;
}

void cell::del_obj()
{
    delete this;
}

double cell::getVal()
{
    return activFun(value);
}

QPointF cell::getPos()
{
    return QPointF(x(),y());
}

void cell::addVal(double val)
{
    value+=val;
    //updateColor();
}

void cell::delVal()
{
    value=bias;
}

void cell::setVal(double val_inp)
{
    value=val_inp;
}

void cell::updateColor()
{
    double val=value;
    if(value>1)val=1;
    if(value<-1)val=-1;

    effect->setOpacity((qAbs(activFun(val))));
    setZValue(qAbs(activFun(val)));
    if(val>0) this->setBrush(Qt::green);
    if(val<=0) this->setBrush(Qt::red);
}

QString cell::getType(){
    return type;
}

QString cell::getGridPos()
{
    return gridPos;
}

void cell::updateInfoBox()
{
    QString str_out="Type: \t"+type+"\nPosition: \t"+gridPos+"\n\n";

    str_out+="Bias: \t" + QString::number(bias)+"\n";
    str_out+="Value: \t" + QString::number(value)+"\n";
    str_out+="Output: \t" + QString::number(activFun(value))+"\n";

    emit setInfoTextUi(str_out);
}

void cell::focusInEvent(QFocusEvent *)
{
    updateInfoBox();
    emit object_selected(this);
}

void cell::focusOutEvent(QFocusEvent *)
{
    //updateColor();
    //emit object_deselected(this);
}
