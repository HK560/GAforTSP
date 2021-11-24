#ifndef LOCATION_H
#define LOCATION_H

#include <QObject>
#include<QtDebug>
class location
{
private:
    int X;
    int Y;
    int code;//地点代号
public:
    location();
    location(int code,int X,int Y);
    void qdebugLocation();
    int getX();
    int getY();
    int getCode();
};

#endif // LOCATION_H
