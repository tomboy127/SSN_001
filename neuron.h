#ifndef NEURON_H
#define NEURON_H

#include <config.h>
#include <cell.h>


class neuron : public cell
{
    Q_OBJECT
public:
    neuron(int l, int n);

    double getVal();
    QPointF getPos();
    QString getType();
    QString getGridPos();
    void addVal(double);

    void del_obj();

    QString type="Neuron";
    QString gridPos;

    double value;
    QGraphicsOpacityEffect *effect;

    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);

signals:
    void setInfoTextUi(QString);

};

#endif // NEURON_H
