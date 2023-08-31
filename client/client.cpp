#include "client.h"
#include <QDebug>
#include <QCoreApplication>

clientDestroyer::~clientDestroyer(){
    delete p_instance;
}

void clientDestroyer::initialize(client * p){
    p_instance = p;
}

QString client::encrypt(QString toEncrypt){
    quint32 key = 562;
    QByteArray arr(toEncrypt.toUtf8());
    for(int i =0; i<arr.size(); i++)
        arr[i] = arr[i] ^ key;

    return QString::fromLatin1(arr.toBase64());
}

QString client::decrypt(QString toDecrypt)
{
    quint32 key = 562;
    QByteArray arr = QByteArray::fromBase64(toDecrypt.toLatin1());
    for(int i =0; i<arr.size(); i++)
        arr[i] = arr[i] ^ key;

    return QString::fromUtf8(arr);
}

client::client(QObject *parent){
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 33333);
    if(mTcpSocket->waitForConnected() ){
            qDebug() << "server active";
    }
     else{
            qDebug() << "server not active";
   }
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &client::slotServerRead);
    Curve *curveSecp256k1 = Curve::getInstance();
    Point k = curveSecp256k1->doublePoint();
    qDebug() << "Here double: " << QString::fromStdString(k.x.str()) << " " << QString::fromStdString(k.y.str());
}

client::~client(){
    mTcpSocket->close();
}

client* client::getInstance(){
    if (!p_instance)
    {
        p_instance = new client();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}


void client::sendToServer(QString message){
    //qDebug() << "encrypted" << encrypt(message).toUtf8();
    mTcpSocket->write(encrypt(message).toUtf8());
    //mTcpSocket->write(message.toUtf8());
}


void client::slotServerRead(){
    QString array = "";
    while(mTcpSocket->bytesAvailable()>0)
    {

        QByteArray res = mTcpSocket->readAll();

        array.append(res);
        array = decrypt(array);
        //mTcpSocket->write(array);
        //qDebug()<< array;
        QStringList list = array.split("&", Qt::SkipEmptyParts);

    }

}
