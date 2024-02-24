#include "mytcpserver.h"

Curve * Curve::pInstance=0;
CurveDestroyer Curve::destroyer;
int Curve::a;
int Curve::b;
uint256_t Curve::p;
Point Curve::G;
Point Curve::O;

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
}

/*конструктор для запуска сервера*/
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "server is not started";
    } else {
        //server_status=1;
        qDebug() << "server is started";
        Curve *curveSecp256k1 = Curve::getInstance();
        Database *db = Database::getInstance();
        Point k = curveSecp256k1->doublePoint();
        QString uuid = QUuid::createUuid().toString();
        qDebug() << "jj 50707738352B416B63737070726577393034696E7676656130686A706B653638" << uuid;

        //qDebug() << "Here double: " << QString::fromStdString(k.x.str()) << " " << QString::fromStdString(k.y.str());
        //Point i = curveSecp256k1->countComposition(83666);
        //qDebug() << "Here mullt: " << QString::fromStdString(i.x.str()) << " " << QString::fromStdString(i.y.str());
        //QString m = "323130393837363534333231303938373635343332313039383736353433323130393837363534333231303938373635343332313039383736353433323130";

        //qDebug() << getHash512(m);
    }
}


/*создание слота для нового подключения*/
void MyTcpServer::slotNewConnection()
{
    QTcpSocket* mTcpSocket = mTcpServer->nextPendingConnection();
    list.push_back(mTcpSocket);
    sockets.insert(mTcpSocket, "");
    qDebug() << mTcpSocket;
    //mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
    connect(mTcpSocket, &QTcpSocket::readyRead,this,&MyTcpServer::slotServerRead);
    connect(mTcpSocket,&QTcpSocket::disconnected,this,&MyTcpServer::slotClientDisconnected);

}

/*чтение строки от пользователя*/
void MyTcpServer::slotServerRead()
{
    Functions f;
    QTcpSocket* mTcpSocket = (QTcpSocket*)sender();
    qDebug() << "info" << mTcpSocket;
    QString res = "";
    while (mTcpSocket->bytesAvailable()>0) {
        QByteArray array = mTcpSocket->readAll();
        res.append(array);
    }
    mTcpSocket->write(f.parse(res).toUtf8());

}

/*возможность подключения нескольких клиентов*/
void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket* mTcpSocket = (QTcpSocket*)sender();
    //qDebug() << "dicsonnected";
    list.removeAt(list.indexOf(mTcpSocket));
    mTcpSocket->close();
    //qDebug() << list.size();
}
