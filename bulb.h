#ifndef BULB_H
#define BULB_H
#include <QString>

class Bulb
{
public:
    Bulb(ushort);
    ~Bulb();
    QString getFullName() const;

private:
    const QString headerName;
    QString fullName;
    ushort id;
};

#endif // BULB_H

