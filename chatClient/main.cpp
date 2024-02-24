#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <QDebug>
#include "client.h"
#include "curve.h"
#include "application.h"
#include <QCoreApplication>

Client * Client::pInstance = 0;
ClientDestroyer Client::destroyer;
QTcpSocket * Client::mTcpSocket;
Curve * Curve::pInstance=0;
CurveDestroyer Curve::destroyer;
int Curve::a;
int Curve::b;
uint256_t Curve::p;
Point Curve::G;
Point Curve::O;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTcpSocket *mTcpSocket = new QTcpSocket();
    mTcpSocket->connectToHost("127.0.0.1", 33333);
    bool connected = mTcpSocket->waitForConnected();
    mTcpSocket->close();
    if (!connected) {
        std::cout << "Server is unavailable. Try later :(";
        return 0;
    }

    Application app;
    app.authentication();
    app.getUserOption();

    return a.exec();
}



