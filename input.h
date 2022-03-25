#ifndef INPUT_H
#define INPUT_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <config.h>


class input : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit input();
    double value;
    void del_obj();
signals:

};

#endif // INPUT_H
