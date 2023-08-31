#ifndef FORMATFUNCTIONS_H
#define FORMATFUNCTIONS_H

#include <QString>
#include <QDebug>
#include <QVector>

typedef QVector<unsigned char> bytesVector;

bytesVector convertHexStrToBytes(QString &hexStr);
QString convertBytesToHexStr(bytesVector &bytes);



#endif // FORMATFUNCTIONS_H
