#ifndef MQV_H
#define MQV_H

#include <QString>
#include <QRegularExpression>
#include <QUuid>
#include "curve.h"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

uint1024_t generateShortTermPrivateKey();
Point MQV(QString login, uint1024_t dA, uint1024_t kA, Point qA, Point rA, Point qB, Point rB);

#endif // MQV_H
