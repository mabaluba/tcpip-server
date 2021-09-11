#include "bulb.h"

Bulb::Bulb(ushort id): headerName("Лампочка № ")
{
    this->id=id;
    this->fullName = this->headerName+QString::number(id);
}
Bulb::~Bulb(){}

QString Bulb::getFullName() const
{
    return this->fullName;
}



