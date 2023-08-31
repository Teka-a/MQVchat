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
        qDebug() << "Here double: " << QString::fromStdString(k.x.str()) << " " << QString::fromStdString(k.y.str());
        Point t = curveSecp256k1->addPoint(k);
        Point i = curveSecp256k1->countComposition(7);
        qDebug() << "Here add: " << QString::fromStdString(t.x.str()) << " " << QString::fromStdString(t.y.str());
        qDebug() << "Here mullt: " << QString::fromStdString(i.x.str()) << " " << QString::fromStdString(i.y.str());
        QString key = "8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef";
        QString plaintext = "1122334455667700ffeeddccbbaa9988";
        QString ciphertext = "7f679d90bebc24305a468d42b9d4edcd";
        qDebug() << "encrypt: " << plaintext << " " << encryptBlock(plaintext, key);
        qDebug() << "decrypt: " << ciphertext << " "<< decryptBlock(ciphertext, key);
        qDebug() << "Hash: " << getHash512("hehe");
    }
}


/*создание слота для нового подключения*/
void MyTcpServer::slotNewConnection()
{
    QTcpSocket* mTcpSocket = mTcpServer->nextPendingConnection();
    list.push_back(mTcpSocket);

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
