#ifndef INPUT_H
#define INPUT_H

#include <config.h>
#include <cell.h>


class input : public cell
{
    Q_OBJECT
public:
    input();

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

#endif // INPUT_H
