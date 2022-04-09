#ifndef OUTPUT_H
#define OUTPUT_H

#include <config.h>
#include <cell.h>


class output : public cell
{
    Q_OBJECT
public:
    output(int l, int p);
    virtual ~output() {};

signals:

};

#endif // OUTPUT_H
