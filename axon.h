#ifndef AXON_H
#define AXON_H

#include <QGraphicsPolygonItem>
#include <QObject>
#include <QDebug>
#include <config.h>
#include "cell.h"
#include <QPolygonF>



class axon : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public: 
    explicit axon(cell* input_ptr, cell* output_ptr);

    void fire();
    void upPos();

    void updateColor();
    void del_obj();

    cell* inp_ptr;
    cell* out_ptr;
    QPolygonF polyg;
    QPointF p1;
    QPointF p2;
    QPointF p3;
    QPointF p4;
    QPointF p5;


    QPointF inpPos;
    QPointF outPos;
    QGraphicsOpacityEffect* effect;

    QString type="Axon";

    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);


    double input=0;
    double weight=0;
    double value=0;
    double opacity=0.5;
signals:
    void setInfoTextUi(QString);

};


#endif // AXON_H
