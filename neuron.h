#ifndef NEURON_H
#define NEURON_H

#include <config.h>
#include <cell.h>


class neuron : public cell
{
public:
    neuron();

    double getVal();
    QPointF getPos();
    void addVal(double);

    void del_obj();


    double value;
    QGraphicsOpacityEffect *effect;

    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);

signals:

};

#endif // NEURON_H
