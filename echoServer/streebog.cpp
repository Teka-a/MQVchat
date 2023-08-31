#include "streebog.h"

void X(const bytesVector &vec1, const bytesVector &vec2, bytesVector &res)
{
    for (int i = 0; i < 64; ++i){
        res[i] = vec1[i] ^ vec2[i];
    }
}

void addInRingOFResidues(const bytesVector &vec1, const bytesVector &vec2, bytesVector &result)
{
    int internal = 0;
    for (int i = 0; i < 64; i++) {
        internal = vec1[i] + vec2[i] + (internal >> 8);
        result[i] = internal & 0xFF;
    }
}

void S(bytesVector &vec)
{
    for (int i = 0; i < 64; ++i){
        vec[i] = pi[vec[i]];
    }
}

void P(bytesVector &vec)
{
    bytesVector temp (64, 0x00);
    for (int i = 0; i < 64; ++i){
        temp[i] = vec[Tau[i]];
    }
    vec = temp;
}

void L(bytesVector &vec)
{
    QVector <bytesVector> internal (8);
    for (int i = 7; i >= 0; --i){
        for (int j = 63; j >= 0; --j){
            if ((vec[i] >> j) & 1)
              internal[i] ^= A[63 - j];
        }
    }
    vec = internal;
}

QString getHash512(const QString &text)
{
    bytesVector h (64, 0x00);
    bytesVector N (64, 0x00);
    bytesVector res (64, 0x00);
    X(h, N, res);
    S(res);
    qDebug() << "S: " << convertBytesToHexStr(res);
    P(res);
    qDebug() << "P: " << convertBytesToHexStr(res);
    L(res);
    qDebug() << "L: " << convertBytesToHexStr(res);
    return text;
}
