#include "curve.h"

CurveDestroyer::~CurveDestroyer()
{
    delete pInstance;
}

void CurveDestroyer::initialize(Curve* p)
{
    pInstance = p;
}

Curve::Curve(QObject *parent)
{
    //Curve secp256k1 parameters
    a = 0;
    b = 7;
    p = 0;
    uint256_t module {"115792089237316195423570985008687907853269984665640564039457584007908834671663"};
    p += module;
    //Curve secp256k1 base point G
    uint256_t gX {"55066263022277343669578718895168534326250603453777594175500187360389116729240"};
    uint256_t gY {"32670510020758816978083085130507043184471273380659243275938904335757337482424"};
    G.x = 0;
    G.y = 0;
    G.x += gX;
    G.y += gY;
    O.x = 0;
    O.y = 0;
}

Curve::~Curve()
{
    qDebug() << "destructoor";
}


Curve* Curve::getInstance()
{
    if (!pInstance) {
        pInstance = new Curve();
        destroyer.initialize(pInstance);
    }
    return pInstance;
}

QString Curve::getModule()
{
    std::string moduleStdString = this->p.str();
    QString module = QString::fromStdString(moduleStdString);
    return module;
}

bool Curve::isInfinityPoint(Point P)
{
    return P.x == 0 && P.y == 0;
}

uint256_t Curve::getInverseElement(uint256_t& x)
{
    //x^(-1) mod p = x^(p-2) mod p
    uint512_t result = 1;
    uint512_t value = x;
    uint256_t pow = this->p - 2;
    while(pow > 0){
        if(pow % 2 == 1){
            result *= value;
            result %= this->p;
        }
        value *= value;
        value %= this->p;
        pow /= 2;
    }

    return (uint256_t)result;

}

Point Curve::addPoint(Point P, Point Q)
{
    Point R;

    if (isInfinityPoint(P) && isInfinityPoint(Q)) {
        return this->O;
    }
    else if (isInfinityPoint(P)) {
        return Q;
    }
    else if (isInfinityPoint(Q)) {
        return P;
    }
    else if (P.x == Q.x && P.y % this->p == (this->p - Q.y) % this->p) {
        return this->O;
    }

    uint256_t element = (uint256_t)(((uint1024_t)Q.x + this->p - P.x) % this->p);
    element = getInverseElement(element);

    uint1024_t lambda = (((((uint1024_t)Q.y + this->p - P.y) % this->p) * element) % this->p);

    R.x = (uint256_t)((((lambda * lambda)% this->p) + (this->p - P.x) + (this->p - Q.x))%this->p);
    R.y = (uint256_t)((((((uint1024_t)P.x + (this->p - R.x)) % this->p) * lambda) % this->p + (this->p - P.y)) % this->p);

    return R;
}

Point Curve::doublePoint(Point P)
{
    Point R;

    uint256_t element = (uint256_t)(((uint1024_t)P.y * 2) % this->p);
    element = getInverseElement(element);

    uint1024_t lambda = (((((uint1024_t)P.x * P.x * 3) % this->p) * element) % this->p);

    R.x = (uint256_t)(((lambda*lambda) % this->p + (this->p - P.x) + (this->p - P.x)) % this->p);
    R.y = (uint256_t)((((((uint1024_t)P.x + (this->p - R.x)) % this->p) * lambda) % this->p + (this->p - P.y)) % this->p);

    return R;
}

Point Curve::countComposition(long long k, Point P)
{
    //Montgomery Ladder
    QString kBin = QString::number(k, 2);

    Point R0 = this->O;
    Point R1 = P;

    for (int i = kBin.length()-1; i >= 0; --i) {
        if (kBin[i] == '0') {
            R0 = doublePoint(R0);
            R1 = addPoint(R0, R1);
        }
        else {
            R0 = addPoint(R0, R1);
            R1 = doublePoint(R1);
        }
    }

    return R0;
}
