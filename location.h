#ifndef LOCATION_H
#define LOCATION_H

#include <QObject>
#include<QtDebug>
class location
{
private:
    int X;
    int Y;
    int code;
public:
    location();
    location(int code,int X,int Y);
    void qdebugLocation();
};

#endif // LOCATION_H
