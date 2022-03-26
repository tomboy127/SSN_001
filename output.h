#ifndef OUTPUT_H
#define OUTPUT_H

#include <config.h>
#include <cell.h>


class output : public cell
{
public:
    output();

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

#endif // OUTPUT_H
