#include "functions.h"

Functions::Functions()
{

}


QString Functions::parse(QString dataFromClient)
{
    qDebug() << "data client" << dataFromClient;

    QStringList list = dataFromClient.split("&", Qt::SkipEmptyParts);
    Curve *curveSecp256k1 = Curve::getInstance();
    Point k = curveSecp256k1->doublePoint();
    qDebug() << "Here double: " << QString::fromStdString(k.x.str()) << " " << QString::fromStdString(k.y.str());
    return "get it!";

}
