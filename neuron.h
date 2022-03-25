#ifndef NEURON_H
#define NEURON_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <config.h>


class neuron : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit neuron();
    double value;
    void del_obj();
signals:

};

#endif // NEURON_H
