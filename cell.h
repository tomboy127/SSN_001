#ifndef CELL_H
#define CELL_H
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QVector2D>
#include <QCoreApplication>
#include <QGraphicsOpacityEffect>
#include <math.h>
#include <random.h>


class cell: public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
public:

    QPointF getPos();
    QString getType();
    QString getGridPos();

    double getVal();
    void delVal();
    void setVal(double);
    void addVal(double);
    void updateColor();
    virtual void updateInfoBox()=0;

    double value;
    double bias;

    QString type;
    QString gridPos;

    QGraphicsOpacityEffect *effect;

    double activFun(double);
    void del_obj();

};

#endif // CELL_H
