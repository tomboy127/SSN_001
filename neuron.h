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

    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);
    virtual void updateInfoBox();

signals:
    void setInfoTextUi(QString);

};

#endif // NEURON_H
