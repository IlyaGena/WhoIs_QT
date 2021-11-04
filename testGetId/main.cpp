#include <QCoreApplication>
#include <QDebug>

#include "temp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Temp tmp(argv[1]);

    return a.exec();
}
