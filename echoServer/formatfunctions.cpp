#include "formatfunctions.h"


bytesVector convertHexStrToBytes(QString &text)
{
    bytesVector bytes;
    bool ok;
    QString temp =  "";
    int hex = 0;
    for(int i = 0; i < text.length() - 1; i += 2){
        temp += text[i];
        temp += text[i+1];
        hex = temp.toInt(&ok, 16);
        bytes.push_back(hex & 0xFF);
        temp = "";
    }
    return bytes;
}

QString convertBytesToHexStr(bytesVector &bytes)
{
    QString temp = "";
    for(auto byte : bytes){
        temp += QString("%1").arg((int)byte, 2, 16, QLatin1Char( '0' ));
    }

    return temp;
}
