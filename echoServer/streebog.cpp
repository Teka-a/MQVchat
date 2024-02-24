#include "streebog.h"

void X(const bytesVector &vec1, const bytesVector &vec2, bytesVector &res)
{
    for (int i = 0; i < vec1.size(); ++i){
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
    //qDebug() << "In L func";
    QString hexStr = convertBytesToHexStr(vec);
    QString binStr = convertHexStrToBinStr(hexStr);
    //QString b = "1010111101010010000011";
    //QString binResult = "";
    //qDebug() << convertBinStrToHexStr(b);
    //b// = "aa";
    //qDebug() << binStr;
    //qDebug() << convertBinStrToHexStr(binStr);
    QString chanks = "";
    bytesVector AElem;
    for (int i = 0; i < 8; ++i) {

        bytesVector temp (8, 0x00);
        //qDebug() << "index" << i*64;
        for (int j = 0; j < 64; ++j) {
            //
            if (binStr[i*64+j] == "1"){
                //temp ^= A[j];
                AElem = convertHexStrToBytes(A[j]);
                X(temp, AElem, temp);
            }
        }
        //qDebug() << QString("%1").arg((long long)temp, 2, 16, QLatin1Char( '0' ));
        //chanks += QString("%1").arg((long long)temp, 2, 16, QLatin1Char( '0' ));
        //qDebug() << convertBytesToHexStr(temp);
        chanks += convertBytesToHexStr(temp);

    }
    qDebug() << "hex" << chanks.length() << chanks;
    vec = convertHexStrToBytes(chanks);
}

QString padding(QString &textBin)
{
    QString padded = "";
    int textBinLength = textBin.length();
    int zeroCount = 511 - textBinLength;
    while (zeroCount != 0) {
        padded += "0";
        zeroCount--;
    }
    padded += "1";
    padded += textBin;
    return convertBinStrToHexStr(padded);
}

bytesVector g(bytesVector h, bytesVector m, bytesVector N)
{
    bytesVector K (64, 0x00);
    bytesVector nextK (64, 0x00);
    bytesVector res (64, 0x00);
    bytesVector prev (64, 0x00);

    X(h, N, K);
    S(K);
    //qDebug() << "S: " << convertBytesToHexStr(res);
    P(K);
    //qDebug() << "P: " << convertBytesToHexStr(res);
    L(K);
    qDebug() << "K: " << convertBytesToHexStr(K);
    prev = m;

    //qDebug() << "After padding: " << m;
    for (int i = 0; i < 12; ++i) {
        qDebug() << i+1;
        qDebug() << "K: " << convertBytesToHexStr(K);
        X(K, prev, res);
        qDebug() << "X: " << convertBytesToHexStr(res);
        S(res);
        qDebug() << "S: " << convertBytesToHexStr(res);
        P(res);
        qDebug() << "P: " << convertBytesToHexStr(res);
        L(res);
        qDebug() << "res: " << convertBytesToHexStr(res);
        prev = res;
        X(K, KeyC[i], nextK);
        //qDebug() << "X: " << convertBytesToHexStr(nextK);
        S(nextK);
        //qDebug() << "S: " << convertBytesToHexStr(nextK);
        P(nextK);
        //qDebug() << "P: " << convertBytesToHexStr(nextK);
        L(nextK);
        qDebug() << "res: " << convertBytesToHexStr(nextK);

        K = nextK;
    }
    X(K, prev, res);
    qDebug() << "X: " << convertBytesToHexStr(res);
    qDebug() << "res: " << convertBytesToHexStr(res);
    qDebug() << "here ";
    X(res, h, res);
    X(res, m, res);

    return res;

}


QString getHash512(QString &text)
{
    //Step 1
    bytesVector h (64, 0x00);
    bytesVector N (64, 0x00);
    bytesVector sigma (64, 0x00);

    QString textBin = convertHexStrToBinStr(text);
    int textBinLength = textBin.length();
    bytesVector m;
    qDebug() << "Before" << textBinLength;
    //Step 2
    if (textBinLength >= 512) {
        //2.2
        int startIndex = textBinLength - 513;
        QString mStr = "";
        for (int i = textBinLength - 513; i < textBinLength; ++i) {
            mStr += textBin[i];
        }
        qDebug() << "Cur len = " << mStr;
        mStr = convertBinStrToHexStr(mStr);
        m = convertHexStrToBytes(mStr);
        qDebug() << "m: " << convertBytesToHexStr(m);

        //2.3
        h = g(h, m, N);
        qDebug() << "res: " << convertBytesToHexStr(h);

        //2.4
        QString hex512 = QString::number(512, 16);

    }



    //Step 3
    QString hexStr = padding(textBin);
    //3.1
    m = convertHexStrToBytes(hexStr);
    //3.2
    h = g(h, m, N);
    qDebug() << "res: " << convertBytesToHexStr(h);
    //3.3
    QString hex = QString::number(textBinLength, 16);
    int zeroCount = 128 - hex.length();
    QString padded = "";
    while (zeroCount != 0) {
        padded += "0";
        zeroCount--;
    }
    padded += hex;
    bytesVector M = convertHexStrToBytes(padded);
    qDebug() << convertBytesToHexStr(M) << M.size();
    addInRingOFResidues(N, M, N);
    qDebug() << convertBytesToHexStr(N);
    //3.4
    addInRingOFResidues(sigma, m, sigma);
    qDebug() << convertBytesToHexStr(sigma);
    //3.5
    bytesVector zeroes (64, 0x00);
    h = g(h, N, zeroes);
    qDebug() << "res: " << convertBytesToHexStr(h);

    h = g(h, sigma, zeroes);
    qDebug() << "res: " << convertBytesToHexStr(h);


    return text;
}
