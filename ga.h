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

    int getPathLength(QVector<int>path, int num);//获取路径总长度
    void tournament(int size,int num);//锦标赛选择,选出交配池
    void getRandomSwitchPoint (int &p1, int &p2,int size);//返回p1,p2两个交叉点,保证p2>p1 距离至少为2
    void crossover(int size,int num,double pc,double pm);//交配
    void removeDuplicates(QVector<int> &path_1, QVector<int> &path_2);//去除重复
    void mutations(QVector<int>&path,int num);//变异
    int getMinPathInPool(int num,QVector<int> &minPath);//取得当前交配池里最短路径长度
    QString outputPath(QVector<int> path);//打印出路径

//    void debugInitRaces();
    void debugPool();
    void debugPath(QVector<int> path);
private:
    QVector<location> loc;//地点位置信息
//    QVector<QVector<int>> initRaces;
    QVector<QVector<int>>* pool=nullptr;//交配池
    QVector<int> minPath;//最小路径
};

#endif // GA_H
