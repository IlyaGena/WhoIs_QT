#ifndef TEMP_H
#define TEMP_H

#include <QObject>
#include "GetIpInfo.h"

#define FILENAME "data.txt"

class Temp : public QObject
{
public:
    Temp(QString ip);

private slots:
    void checkInfo();

    GetIpInfo tmp;
};

#endif // TEMP_H
