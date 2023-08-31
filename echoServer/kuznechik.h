#ifndef KUZNECHIK_H
#define KUZNECHIK_H

#include <QString>
#include <QDebug>
#include <QVector>

#include "constants.h"
#include "formatfunctions.h"


void performXTransformation(bytesVector &vec1, bytesVector &vec2, bytesVector &result);
unsigned char multiplicateInGaluaField(unsigned char &a, unsigned char &b);

void performSTransformation(bytesVector &vec);
void performReverseSTransformation(bytesVector &vec);

void performLTransformation(bytesVector &vec);
void performReverseLTransformation(bytesVector &vec);

void performRTransformation(bytesVector &state);
void performReverseRTransformation(bytesVector &vec);

QVector<bytesVector> expandKey(QString &key);


QString encryptBlock(QString &text, QString &key);
QString decryptBlock(QString &text, QString &key);



#endif // KUZNECHIK_H
