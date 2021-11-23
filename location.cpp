#include "location.h"

location::location()
{

}

location::location(int code,int X,int Y)
{
    this->X=X;
    this->Y=Y;
    this->code=code;
}

void location::qdebugLocation()
{
    qDebug()<<QString("NUM:%1 X=%2 Y=%3").arg(this->code).arg(this->X).arg(this->Y);

}

int location::getX()
{
    return this->X;
}

int location::getY()
{
    return this->Y;
}


int location::getCode()
{
    return this->code;
}
