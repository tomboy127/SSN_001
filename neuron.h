#ifndef NEURON_H
#define NEURON_H

#include <config.h>
#include <cell.h>


class neuron : public cell
{
    Q_OBJECT
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
    void setInfoTextUi(QString);

};

#endif // NEURON_H
