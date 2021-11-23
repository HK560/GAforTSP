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
    void init_races(int size,int num);//初始化种群
    void debugInitRaces();
    void debugPool();
    void debugPath(QVector<int> path);
    int getPathLength(QVector<int>path, int num);//获取路径总长度
    void tournament(int size);//锦标赛选择,选出交配池
    void getRandomSwitchPoint (int &p1, int &p2,int size);//返回p1,p2两个交叉点,保证p2>p1 距离至少为2
    void crossover(int size,double pc);
    void removeDuplicates(QVector<int>&path_1,QVector<int>&path_2);
private:
    QVector<location> loc;
    QVector<QVector<int>> initRaces;
    QVector<QVector<int>>* pool;
};

#endif // GA_H
