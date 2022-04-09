#ifndef NEURON_H
#define NEURON_H

#include <config.h>
#include <cell.h>


class neuron : public cell
{
    Q_OBJECT
public:
    neuron(int l, int n);
    virtual ~neuron() {};

signals:

};

#endif // NEURON_H
