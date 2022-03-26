#ifndef INPUT_H
#define INPUT_H

#include <config.h>
#include <cell.h>


class input : public cell
{
    Q_OBJECT
public:
    input(int l, int p);

    double getVal();
    QPointF getPos();
    QString getType();
    QString getGridPos();

    void addVal(double);

    void del_obj();

    QString type="Input";
    QString gridPos;

    double value;
    QGraphicsOpacityEffect *effect;

    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);

signals:
    void setInfoTextUi(QString);

};

#endif // INPUT_H
