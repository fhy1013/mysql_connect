#ifndef DATABASECONTRAL_H
#define DATABASECONTRAL_H


#include <QCoreApplication>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QObject>

class DatabaseContral
{
public:
    DatabaseContral();
    ~DatabaseContral();

    bool Connect_Database(const QString ip,int port,const QString dataname,const QString user,const QString password);
    void Disconnect_Database();
    bool Ins_Del_Upd_Database(const QString str);
//    bool Ins_Del_Upd_Database(const QByteArray str);
    QSqlQuery Select_Database(const QString str);
    bool Commit();
    bool RollBack();
private:
    QSqlDatabase *db;
};

#endif // DATABASECONTRAL_H
