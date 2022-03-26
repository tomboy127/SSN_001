#ifndef INPUT_H
#define INPUT_H

#include <config.h>
#include <cell.h>


class input : public cell
{
public:
    input();

    double getVal();
    QPointF getPos();
    void addVal(double);

    void del_obj();


    double value;

signals:

};

#endif // INPUT_H
