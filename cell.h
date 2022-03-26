#ifndef CELL_H
#define CELL_H
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QVector2D>
#include <QCoreApplication>
#include <QGraphicsOpacityEffect>
#include <math.h>


class cell: public QObject, public QGraphicsEllipseItem{    
public:
    virtual double getVal()=0;
    virtual QPointF getPos()=0;
    virtual void addVal(double)=0;
    virtual void del_obj()=0;

    //virtual QVector2D getForce(int=0)=0;
    //virtual QVector2D getVel()=0;

    //virtual void addForce(QVector2D, int=0)=0;
    //virtual void move()=0;

};

#endif // CELL_H
