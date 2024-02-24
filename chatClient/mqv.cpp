#include "mqv.h"

uint1024_t generateShortTermPrivateKey()
{
    QString uuid = QUuid::createUuid().toString();
    uuid.remove(QRegularExpression("{|}"));
    QStringList partsUuid = uuid.split("-", Qt::SkipEmptyParts);
    bool ok;
    uint1024_t shortTermPrivateKey {std::to_string(partsUuid[3].toLongLong(&ok, 16))};
    //Point shortTermOpenKey = Curve::getInstance()->countComposition(shortTermPrivateKey);
    return shortTermPrivateKey;
}

Point MQV(QString login, uint1024_t dA, uint1024_t kA, Point qA, Point rA, Point qB, Point rB)
{
    //std::cout << "MQV";
    Curve *secp256k1 = Curve::getInstance();
    //qDebug() << "private Short" << QString::fromStdString(kA.str());
    //My open keys
    //shortTerm
    //qDebug() << "My short open: " << QString::fromStdString(rA.x.str()) << " " << QString::fromStdString(rA.y.str());
    uint1024_t xA = (uint1024_t)rA.x;
    //longTerm
    //qDebug() << "My long open: " << QString::fromStdString(qA.x.str()) << " " << QString::fromStdString(qA.y.str());
    uint256_t aA = qA.x;
    //Other's open keys
    //shortTerm
    //qDebug() << "Server short open: " << QString::fromStdString(rB.x.str()) << " " << QString::fromStdString(rB.y.str());
    uint1024_t xB = (uint1024_t)rB.x;
    //longTerm
    //qDebug() << "Server long open: " << QString::fromStdString(qB.x.str()) << " " << QString::fromStdString(qB.y.str());
    uint1024_t aB = (uint1024_t)qB.x;

    //qDebug() << "MQV stage 1";

    uint1024_t sA = xA*aA*dA;
    sA += kA;
    sA %= (uint1024_t)secp256k1->getN().toStdString();
    //qDebug() << "sA =" << QString::fromStdString(sA.str());


    //qDebug() << "MQV stage 2";


    Point uA = secp256k1->countComposition(aB, qB);
    uA = secp256k1->countComposition(xB, uA);
    uA = secp256k1->addPoint(rB, uA);
    //qDebug() << "uA" << QString::fromStdString(uA.x.str()) << QString::fromStdString(uA.y.str());

    //qDebug() << "MQV stage 3";
    Point W = secp256k1->countComposition(sA, uA);
    //qDebug() << "W" << QString::fromStdString(W.x.str()) << QString::fromStdString(W.y.str());

    return W;
}
