#include <QCoreApplication>
#include "mytcpserver.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyTcpServer myserv;

    return a.exec();
}
