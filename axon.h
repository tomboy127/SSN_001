#ifndef AXON_H
#define AXON_H

#include <QGraphicsPolygonItem>
#include <QObject>
#include <config.h>

class axon : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    //explicit axon(neuron ptr);

signals:

};

/*
    explicit input();
    double value;
    void del_obj();
signals:

};
*/

#endif // AXON_H
