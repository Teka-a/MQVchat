#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <QRegularExpression>
#include <QUuid>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "curve.h"
#include "database.h"
#include "kuznechik.h"

class Functions
{
private:
    QSqlDatabase *db;
    Curve *secp256k1;
    Point shortTermOpenKey;
    QString sendOpenKey(QString login);
    QString sendShortTermOpenKey(QString login);
    void generateShortTermKey(uint1024_t &shortTermPrivateKey);
    void mqv(Point longTermOpenKey, Point shortTermOpenKey);

public:
    Functions();
    QString parse(QString dataFromClient);
    QString convertTextToHex(QString text);

};

#endif // FUNCTIONS_H
