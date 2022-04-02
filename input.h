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

    void focusInEvent(QFocusEvent*);
    void focusOutEvent(QFocusEvent*);
    virtual void updateInfoBox();

signals:
    void setInfoTextUi(QString);
    void object_selected(cell*);
    //void object_deselected(cell*);
};

#endif // INPUT_H
