#ifndef OUTPUT_H
#define OUTPUT_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <config.h>


class output : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit output();
    double value;
    void del_obj();
signals:

};

#endif // OUTPUT_H
