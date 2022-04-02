#include "axon.h"
#include <QGraphicsView>




axon::axon(cell* input_ptr, cell* output_ptr)
{    
  weight=rnd11();
  value=weight;

  setFlag(QGraphicsItem::ItemIsFocusable);

  effect = new QGraphicsOpacityEffect(this);
  this->setGraphicsEffect(effect);
  updateColor();


  inp_ptr=input_ptr;
  out_ptr=output_ptr;

  inpPos=inp_ptr->getPos();
  outPos=out_ptr->getPos();


  upPos();
}

void axon::fire()
{
    input=inp_ptr->getVal();
    value=input*weight;
    out_ptr->addVal(value);
}

void axon::upPos()
{


    inpPos=inp_ptr->getPos();
    outPos=out_ptr->getPos();

    //qDebug()<<"inpPos: "<<inpPos;
   // qDebug()<<"outPos: "<<outPos<<"";

    QVector2D dist1=QVector2D((out_ptr->getPos().x()-inp_ptr->getPos().x()),(out_ptr->getPos().y()-inp_ptr->getPos().y()));

    const int w=4;
    const int l_disp=dist1.length()/2-DOTSIZE/2-2;

    p1.setX(inpPos.x()+dist1.x()/2);p1.setY(inpPos.y()+dist1.y()/2);

    p2.setX(p1.x()+l_disp);p2.setY(p1.y()-w);
    p3.setX(p1.x()+l_disp);p3.setY(p1.y()+w);
    p4.setX(p1.x()-l_disp);p4.setY(p1.y()-w);
    p5.setX(p1.x()-l_disp);p5.setY(p1.y()+w);

    polyg.clear();
    polyg<<p1<<p2<<p3<<p1<<p4<<p5;
    this->setPolygon(polyg);

    this->setTransformOriginPoint(p1);
    this->setRotation(180.0/M_PI*atan2(dist1.y(),dist1.x()));


}

void axon::updateColor()
{
    double val=value;
    if(val>1)val=1;
    if(val<-1)val=-1;

    if(val>=0) this->setBrush(Qt::green);
    if(val<0) this->setBrush(Qt::red);
    effect->setOpacity(qAbs(val));
}

void axon::focusInEvent(QFocusEvent *)
{
    this->setBrush(Qt::yellow);
    effect->setOpacity(0.8);
    setZValue(1);

    QString str_out="Type: \t"+type+"\nPath: \t";
    str_out+=inp_ptr->getGridPos()+" -> "+out_ptr->getGridPos()+"\n\n";

    str_out+="Input: \t" + QString::number(input)+"\n";
    str_out+="Weight: \t" + QString::number(weight)+"\n";
    str_out+="Output: \t" + QString::number(value)+"\n";


    emit setInfoTextUi(str_out);
}

void axon::focusOutEvent(QFocusEvent *)
{
    updateColor();
    setZValue(0);
    emit setInfoTextUi("Select object");
}

void axon::del_obj()
{
    delete this;
}
