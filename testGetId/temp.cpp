#include "temp.h"

Temp::Temp(QString ip) :
    tmp(this, FILENAME)
{
    qDebug() << ip;

    tmp.checkIp(ip);
    connect(&tmp, &GetIpInfo::getInfoIp, this, &Temp::checkInfo);
}

void Temp::checkInfo()
{
    QFile file(FILENAME);

    if(!file.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&file);

    while(!stream.atEnd()) {
        QString line = stream.readLine();
        qDebug() << line;
    }

    file.close();
}
