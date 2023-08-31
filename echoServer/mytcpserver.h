/*#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H


class mytcpserver
{
public:
    mytcpserver();
};

#endif // MYTCPSERVER_H*/
#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QList>
#include <QCoreApplication>

#include "curve.h"
#include "functions.h"
#include "database.h"
#include "kuznechik.h"
#include "streebog.h"

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
private:
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
    /**
     * @brief список подключенний, сокетов
     */
    QList<QTcpSocket*> list;
    //int server_status;
};
#endif // MYTCPSERVER_H
