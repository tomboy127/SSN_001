#ifndef INPUT_H
#define INPUT_H

#include <config.h>
#include <cell.h>


class input : public cell
{
    Q_OBJECT
public:
    input(int l, int p);
    virtual ~input() {};
    void delVal();

signals:
};

#endif // INPUT_H
