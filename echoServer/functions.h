#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<QString>
#include "curve.h"
#include "kuznechik.h"

class Functions
{
public:
    Functions();
    QString parse(QString dataFromClient);
    QString convertTextToHex(QString text);
};

#endif // FUNCTIONS_H
