#include "databasecontral.h"

DatabaseContral::DatabaseContral()
{
    db = new QSqlDatabase();
    *db =  QSqlDatabase::addDatabase("QMYSQL");
}
DatabaseContral::~DatabaseContral(){
    delete db;
}

/* 连接mysql数据库 */
bool DatabaseContral::Connect_Database(const QString ip,int port,const QString dataname,const QString user,const QString password)
{

    if(db->isOpen() == false)
    {
        db->setHostName(ip);      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
        db->setPort(port);                 //连接数据库端口号，与设置一致
        db->setDatabaseName(dataname);      //连接数据库名，与设置一致
        db->setUserName(user);          //数据库用户名，与设置一致
        db->setPassword(password);    //数据库密码，与设置一致
        db->open();
        if(!db->open())
        {
            qDebug()<<"不能连接"<<"connect to mysql error"<<db->lastError().text();
            return false;
        }
        else
        {
            qDebug()<<"连接成功"<<"connect to mysql OK";
            return true;
        }
    }
    return true;
}

/* 断开mysql数据库 */
void DatabaseContral::Disconnect_Database()
{
    if(db->isOpen())
    {
        db->close();

    }

}

/* 数据库的增,删,改功能 */
bool DatabaseContral::Ins_Del_Upd_Database(const QString str)
//bool DatabaseContral::Ins_Del_Upd_Database(const QByteArray str)
{
    QSqlQuery query(*db);
    query.prepare(str);
    return query.exec();
}

/* 数据库查询功能 */
QSqlQuery DatabaseContral::Select_Database(const QString str)
{
    QSqlQuery query(*db);
    query.prepare(str);
    query.exec();

    return query;
}

/*
*   功能：
*       提交
*   参数：
*       const QString &table_name I 表名
*/
bool DatabaseContral::Commit(){
    QString sql = "commit;";
    QSqlQuery query(*db);
    query.prepare(sql);
    return query.exec();
}


/*
*   功能：
*       回滚
*   参数：
*       const QString &table_name I 表名
*/
bool DatabaseContral::RollBack(){
    QString sql = "rollback;";
    QSqlQuery query(*db);
    query.prepare(sql);
    return query.exec();
}
