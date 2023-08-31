#include "myfunctions.h"
#include <QDebug>
#include <QString>


QString myfunctions::parsing(QString data_from_client)
{
    qDebug() << "data client" << data_from_client;
    QStringList list = data_from_client.split("&", Qt::SkipEmptyParts);
    Curve *curveSecp256k1 = Curve::getInstance();
    Point k = curveSecp256k1->doublePoint();
    qDebug() << "Here double: " << QString::fromStdString(k.x.str()) << " " << QString::fromStdString(k.y.str());
    return "get it!";

}
