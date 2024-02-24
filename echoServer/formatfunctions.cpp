#include "formatfunctions.h"

QString convertHexStrToBinStr(QString &hexStr)
{

    QString binStr = "";
    for (int i = 0; i < hexStr.length(); ++i) {
        binStr += hexToBinMap[hexStr[i]];
    }
    return binStr;
}

QString convertBinStrToHexStr(QString &binStr)
{
    QString hexStr = "";
    QString tempBin;
    while (binStr.length() % 4 != 0) {
        binStr = "0" + binStr;
    }
    for (int i = 0; i < binStr.length(); i+=4){
        tempBin = "";
        for (int j = 0; j < 4; ++j){
            tempBin += binStr[i+j];
        }
        hexStr += binToHexMap[tempBin];
    }
    return hexStr;
}

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
        //qDebug() << "char: " << QString("%1").arg((int)byte, 2, 16, QLatin1Char( '0' ));
        temp += QString("%1").arg((int)byte, 2, 16, QLatin1Char( '0' ));
    }

    return temp;
}
