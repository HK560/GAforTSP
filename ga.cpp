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

void GA::debugPool()
{
    Q_ASSERT(this->pool->size()>0);
    qDebug()<<"pool:";
    for(auto i=pool->begin();i!=pool->end();i++){
        QDebug debug=qDebug();
        debug<<"[";
        for(int k=0;k<i->size();k++){
            debug<<i->at(k);
        }
        debug<<"]";
    }
}

void GA::debugPath(QVector<int> path)
{
    qDebug()<<"debugPath:";
    QDebug debug=qDebug();
    debug<<"[";
    for(auto i=path.begin();i!=path.end();i++){
        debug<<*i;
    }
    debug<<"]";
}

int GA::getPathLength(QVector<int>path, int num)
{
    qDebug()<<"getpathlength";
    Q_ASSERT(num==path.size());
    int pathLength=0;
    for(int k=0;k<path.size();k=k+2){
        pathLength+=sqrt(pow(qAbs((this->loc[path[k]].getX())-(this->loc[path[k+1]].getX())),2)+pow(qAbs((this->loc[path[k]].getY())-(this->loc[path[k+1]].getY())),2));

    }
    qDebug()<<"nowpath:"<<pathLength;
    return pathLength;
}

void GA::tournament(int size,int num)
{
    qDebug()<<"tournament";
    Q_ASSERT(size>0);
    this->pool=new QVector<QVector<int>>;
    int time=size;
    while(time--){
        int index_1=QRandomGenerator::system()->bounded(size);
        int index_2=QRandomGenerator::system()->bounded(size);
        if(getPathLength(this->initRaces[index_1],num)>getPathLength(this->initRaces[index_2],num)){
            this->pool->append(this->initRaces[index_1]);
        }else{
            this->pool->append(this->initRaces[index_2]);
        }
    }
    debugPool();
}

void GA::getRandomSwitchPoint(int &p1,int &p2,int num)
{
    //Q_ASSERT(p1>=0&&p2>=0);
    int tmp1,tmp2;
    do{
        tmp1=QRandomGenerator::system()->bounded(num);
        tmp2=QRandomGenerator::system()->bounded(num);
    }while(tmp1>=tmp2&&!((tmp2-tmp1)>=2));
    p1=tmp1;
    p2=tmp2;
}

void GA::crossover(int size,int num,double pc)
{
    Q_ASSERT(this->pool->size()>0);
    Q_ASSERT(size>0&&num>0);
    Q_ASSERT(pc>=0&&pc<=1);
    QVector<QVector<int>>* newPool=new  QVector<QVector<int>>;
    int time=size;
    while (time--) {
        int rand_1=QRandomGenerator::system()->bounded(size);
        int rand_2=QRandomGenerator::system()->bounded(size);
        QVector<int> tmpPath_1=this->pool->at(rand_1);
        QVector<int> tmpPath_2=this->pool->at(rand_2);
        debugPath(tmpPath_1);
        debugPath(tmpPath_2);
        double randPC=double(QRandomGenerator::system()->bounded(1.0));
        qDebug()<<"randpc:"<<randPC;
        Q_ASSERT(randPC<1&&rand()>=0);
        if(randPC<pc){
            qDebug()<<"directADD";
            newPool->append(tmpPath_1);
            newPool->append(tmpPath_2);
        }else{
            qDebug()<<"jiaocha";
            int crossPos_1,crossPos_2;
            getRandomSwitchPoint(crossPos_1,crossPos_2,size);
            Q_ASSERT(crossPos_2>crossPos_1);
           // QVector<int> tmpp;
            for(int i=crossPos_1;i<crossPos_2;i++){
                int tmppp=tmpPath_1[i];
                tmpPath_1[i]=tmpPath_2[i];
                tmpPath_2[i]=tmppp;
            }
            debugPath(tmpPath_1);
            debugPath(tmpPath_2);
            removeDuplicates(tmpPath_1,tmpPath_2,size);
            newPool->append(tmpPath_1);
            newPool->append(tmpPath_2);
        }
    }

}

void GA::removeDuplicates(QVector<int> &path_1, QVector<int> &path_2,int size)
{
    qDebug()<<"removeDuplicates";
    QVector<int> duplicates_1;
    for(auto i=path_1.begin();i!=path_1.end();i++){
//        Q_ASSERT(i<size&&i>=0);
        if(path_1.count(*i)>1){
            if(duplicates_1.contains(*i)==false)
                duplicates_1.append(*i);
        }
    }
    QVector<int> duplicates_2;
    for(auto i=path_2.begin();i!=path_2.end();i++){
        //Q_ASSERT(*i<size&&*i>=0);
        if(path_2.count(*i)>1){
            if(duplicates_2.contains(*i)==false)
                duplicates_2.append(*i);
        }
    }
    int rr=duplicates_1[0];
    debugPath(duplicates_1);
    debugPath(duplicates_2);
    qDebug()<<rr;
    Q_ASSERT(duplicates_1.size()==duplicates_2.size());
    for(int i=0;i<duplicates_1.size();i++){
        int tmp= path_1[path_1.indexOf(duplicates_1[i])];
        path_1[path_1.indexOf(duplicates_1[i])]=duplicates_2[i];
        path_2[path_2.indexOf(duplicates_2[i])]=tmp;

    }
    debugPath(path_1);
    debugPath(path_2);


}

void GA::mutations(QVector<int> &path,int num)
{
    int randIndex_1=QRandomGenerator::system()->bounded(num);
    int randIndex_2=QRandomGenerator::system()->bounded(num);
    if(randIndex_1!=randIndex_2){
        int tmp=path[randIndex_1];
        path[randIndex_1]=path[randIndex_2];
        path[randIndex_2]=tmp;
    }

}
