#include "ga.h"

GA::GA()
{//初始化，添加地点信息
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
    Q_ASSERT(this->pool==nullptr);
    this->pool=new QVector<QVector<int>>;
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
        this->pool->append(now);
    }
}

//void GA::debugInitRaces()
//{
//    for(auto i=initRaces.begin();i!=initRaces.end();i++){
//        QDebug debug=qDebug();
//        debug<<"[";
//        for(int k=0;k<i->size();k++){
//            debug<<i->at(k);
//        }
//        debug<<"]";
//    }
//}

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

double GA::getPathLength(QVector<int>path, int num)
{
    qDebug()<<"getpathlength";
    Q_ASSERT(num==path.size());
    double pathLength=0;
    for(int k=0;k<path.size()-1;k++){
        pathLength+=sqrt(pow(qAbs((this->loc[path[k]].getX())-(this->loc[path[k+1]].getX())),2)+pow(qAbs((this->loc[path[k]].getY())-(this->loc[path[k+1]].getY())),2));
//        pathLength+=qAbs((this->loc[path[k]].getX())-(this->loc[path[k+1]].getX()))+qAbs((this->loc[path[k]].getY())-(this->loc[path[k+1]].getY()));
    }
//    int end=path.last()
//    pathLength+=qAbs((this->loc[path.last()].getX())-(this->loc[path.first()].getX()))+qAbs((this->loc[path.last()].getY())-(this->loc[path.first()].getY()));
    pathLength+=sqrt(pow(qAbs((this->loc[path.last()].getX())-(this->loc[path.first()].getX())),2)+pow(qAbs((this->loc[path.last()].getY())-(this->loc[path.first()].getY())),2));
    qDebug()<<"nowpath:"<<pathLength;
    return pathLength;
}

void GA::tournament( int size,int num)
{
    qDebug()<<"tournament";
    Q_ASSERT(size>0);
//    this->pool=new QVector<QVector<int>>;

    QVector<QVector<int>> *newpool=new QVector<QVector<int>>;
    int time=size;
    while(time--){
        int index_1=QRandomGenerator::system()->bounded(size);
        int index_2=QRandomGenerator::system()->bounded(size);
        if(getPathLength(this->pool->at(index_1),num)<getPathLength(this->pool->at(index_2),num)){
            newpool->append(this->pool->at(index_1));
        }else{
            newpool->append(this->pool->at(index_2));
        }
    }
    delete this->pool;
    this->pool=newpool;
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

void GA::crossover(int size,int num,double pc,double pm)
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
            removeDuplicates(tmpPath_1,tmpPath_2);
            double randPM=double(QRandomGenerator::system()->bounded(1.0));
            if(randPM<pm){
                qDebug()<<"mutations";
                mutations(tmpPath_1,num);
                mutations(tmpPath_2,num);
                debugPath(tmpPath_1);
                debugPath(tmpPath_2);
            }

            newPool->append(tmpPath_1);
            newPool->append(tmpPath_2);
        }
    }
    delete pool;
    pool=newPool;

}

void GA::removeDuplicates(QVector<int> &path_1, QVector<int> &path_2)
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
    if(duplicates_1.size()>0){
        debugPath(duplicates_1);
        debugPath(duplicates_2);
        Q_ASSERT(duplicates_1.size()==duplicates_2.size());
        for(int i=0;i<duplicates_1.size();i++){
            int tmp= path_1[path_1.indexOf(duplicates_1[i])];
            path_1[path_1.indexOf(duplicates_1[i])]=duplicates_2[i];
            path_2[path_2.indexOf(duplicates_2[i])]=tmp;

        }
        debugPath(path_1);
        debugPath(path_2);
    }
    //int rr=duplicates_1[0];



}

inline void GA::mutations(QVector<int> &path,int num)
{
    int randIndex_1=QRandomGenerator::system()->bounded(num);
    int randIndex_2=QRandomGenerator::system()->bounded(num);
    if(randIndex_1!=randIndex_2){
        int tmp=path[randIndex_1];
        path[randIndex_1]=path[randIndex_2];
        path[randIndex_2]=tmp;
    }

}

double GA::getMinPathInPool(int num,QVector<int> &minPath)
{
    int min=INT32_MAX;

    for(auto i= this->pool->begin();i!=this->pool->end();i++){
        double pathvalue=getPathLength(*i,num);
        if(pathvalue<min){
            minPath=*i;
            min=pathvalue;
            this->minPath=*i;
        }
    }
    return min;
}

QString GA::outputPath(QVector<int> path)
{
    QString output;
    output.append("[");
    for(auto i= path.begin();i!=path.end();i++){
        output.append(QString::number(this->loc[*i].getCode()));
        output.append(" ");
    }
    output.append("]");
    return output;
}
