#include "ga.h"

GA::GA()
{
    loc.append(location(1,87,7));
    loc.append(location(2,91,38));
    loc.append(location(3,83,46));
    loc.append(location(4,71,44));
    loc.append(location(5,64,60));
    loc.append(location(6,68,58));
    loc.append(location(7,83,69));
    loc.append(location(8,87,76));
    loc.append(location(9,74,78));
    loc.append(location(10,71,71));
    loc.append(location(11,58,62));
    loc.append(location(12,54,62));
    loc.append(location(13,51,67));
    loc.append(location(14,37,84));
    loc.append(location(15,41,94));
    loc.append(location(16,2,99));
    loc.append(location(17,7,64));
    loc.append(location(18,22,60));
    loc.append(location(19,25,62));
    loc.append(location(20,18,54));
    loc.append(location(21,4,50));
    loc.append(location(22,13,40));
    loc.append(location(23,18,40));
    loc.append(location(24,24,42));
    loc.append(location(25,25,38));
    loc.append(location(26,41,26));
    loc.append(location(27,45,35));
    loc.append(location(28,44,35));
    loc.append(location(29,58,35));
    loc.append(location(30,62,32));
}

void GA::init_races(int size,int num)
{


    for(int i=0;i<size;i++){
        QVector<int> now;
         int tmprand;
         QVector<bool> tmp(num,false);
        for(int k=0;k<num;k++){
            do{
                tmprand=QRandomGenerator::global()->bounded(num);
            }
            while (tmp.at(tmprand)==true);
//            qDebug()<<tmprand;
           tmp[tmprand]=true;
           now.append(tmprand);
        }
        this->initRaces.append(now);
    }
}

void GA::debugInitRaces()
{
    for(auto i=initRaces.begin();i!=initRaces.end();i++){
        QDebug debug=qDebug();
        debug<<"[";
        for(int k=0;k<i->size();k++){
            debug<<i->at(k);
        }
        debug<<"]";
    }
}

void GA::getPathLength(QVector<int>path, int num)
{
    int pathLength=0;
    for(int k=0;k<num;k=k+2){
        pathLength+=sqrt(pow(qAbs((this->loc[path[k]].getX())-(this->loc[path[k+1]].getX())),2)+pow(qAbs((this->loc[path[k]].getY())-(this->loc[path[k+1]].getY())),2));
        qDebug()<<"nowpath:"<<pathLength;
    }
}
