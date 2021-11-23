#ifndef GA_H
#define GA_H

#include "location.h"
#include <QVector>
#include<QRandomGenerator>
#include<QDebug>
class GA
{
public:
    GA();
    void init_races(int size,int num);
    void debugInitRaces();

private:
    QVector<location> loc;
    QVector<QVector<int>> initRaces;
};

#endif // GA_H
