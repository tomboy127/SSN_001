#include "random.h"

double rnd11(double low, double high){

    double output;
    output=rand()%int((high-low)*1024);
    output/=1024;
    output+=low;
    //_sleep(rand()%50);

    //qDebug()<<QString::number(output);

    return output;
}
