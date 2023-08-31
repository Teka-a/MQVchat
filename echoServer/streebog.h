#ifndef STREEBOG_H
#define STREEBOG_H

#include <QString>
#include <QDebug>
#include <QVector>

#include "constants.h"
#include "formatfunctions.h"


void X(const bytesVector &vec1, const bytesVector &vec2, bytesVector &res);
void S(bytesVector &vec);
void P(bytesVector &vec);
void L(bytesVector &vec);
void addInRingOFResidues(const bytesVector &vec1, const bytesVector &vec2, bytesVector &result);

QString getHash512(const QString &text);

#endif // STREEBOG_H
