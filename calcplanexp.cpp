#include "calcplanexp.h"



void testM()
{
    double t[4] = {0.2, 0.2, 0.19, 0.19};

    const auto b0 = (t[0] + t[1] + t[2] + t[3]) / 4;
    const auto b1 = (-t[0] + t[1] - t[2] + t[3]) / 4;
    const auto b2 = (-t[0] - t[1] + t[2] + t[3]) / 4;
    const auto b12 = (t[0] - t[1] - t[2] + t[3]) / 4;

    qDebug()<<b0 <<endl<<b1 <<endl<<b2 <<endl<<b12 <<endl;
}
