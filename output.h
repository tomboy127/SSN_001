#ifndef OUTPUT_H
#define OUTPUT_H

#include <config.h>
#include <cell.h>


class output : public cell
{
    Q_OBJECT
public:
    output(int l, int p);

    double getVal();
    QPointF getPos();
    QString getType();
    QString getGridPos();
    void addVal(double);

    void del_obj();

    QString type="Output";
    QString gridPos;

    double value;
    QGraphicsOpacityEffect *effect;

    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);

signals:
    void setInfoTextUi(QString);

};

#endif // OUTPUT_H
