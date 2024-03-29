#include "database.h"

Database * Database::pInstance=0;
DatabaseDestroyer Database::destroyer;

DatabaseDestroyer::~DatabaseDestroyer()
{
    qDebug() << "deleted";
    delete pInstance;
}

void DatabaseDestroyer::initialize(Database * p)
{
    qDebug() << "initialize";
    pInstance = p;
}

Database * Database::getInstance()
{
    qDebug() << "get instance";
    if (!pInstance) {
        pInstance = new Database();
        destroyer.initialize(pInstance);
    }
    return pInstance;
}

Database::Database()
{
    qDebug() << "constructor";
    database = QSqlDatabase::addDatabase("QPSQL");
    database.setDatabaseName("secretchat");
    database.setUserName("server");
    database.setPassword("S!Pk1_3rriL");

    if (!database.open()){
        qDebug() << "nope" << database.lastError().text();
    }
    else
        qDebug() << "ok";

}

void Database::closeDatabase()
{
    if (database.open()) {
        database.close();
        qDebug() << "closed";
    }
    else
        qDebug() << "already closed";
}

Database::~Database()
{

}
