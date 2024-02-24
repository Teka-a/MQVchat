#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include "curve.h"
#include "client.h"
#include "communication.h"
#include "mqv.h"
#include "kuznechik.h"


class Application : public QObject
{
    Q_OBJECT

public:
    explicit Application();
    ~Application();
    void getUserOption();
    void authentication();
private:
    Curve *secp256k1;
    //additional
    void formString30(std::string &option);
    //functionality
    void end();
    void showHelp();

signals:
    void finished();
private slots:
    void checkSecretKey(Point openKey);
    void shareSecret(Point longTermOpenKey, Point shortTermOpenKey);
};

#endif // APPLICATION_H
