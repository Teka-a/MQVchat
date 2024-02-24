#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <QObject>
#include "curve.h"
#include "client.h"
#include "communication.h"
#include "mqv.h"

class Authentication : public QObject
{
    Q_OBJECT

public:
    explicit Authentication();
    ~Authentication();
    void authentication();

private slots:
    void checkSecretKey(Point openKey);
    void shareSecret(Point longTermOpenKey, Point shortTermOpenKey);
signals:
    void authStatus(int status);
private:
    Curve *secp256k1;
};

#endif // AUTHENTICATION_H
