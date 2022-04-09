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
    void updateInfoBox();

    double value;
    double bias;

    QString type;
    QString gridPos;

    QGraphicsOpacityEffect *effect;

    double activFun(double);
    void del_obj();

    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);

signals:
     void setInfoTextUi(QString);
     void object_selected(cell*);
     //void object_deselected(cell*);

};

#endif // CELL_H
