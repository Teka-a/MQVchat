#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


class Database;

class DatabaseDestroyer{
private:
    Database * pInstance;
public:
    ~DatabaseDestroyer();
    void initialize(Database * p);
};


class Database
{
private:
    static Database * pInstance;
    static DatabaseDestroyer destroyer;
    QSqlDatabase database;
protected:
    Database();
    Database(const Database&);
    Database & operator= (Database&);
    ~Database();
    friend class DatabaseDestroyer;
public:
    static Database * getInstance();
    void closeDatabase();
};

#endif // DATABASE_H
