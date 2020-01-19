#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include <QDateTime>

#include "databasecontral.h"

bool verifyHexDataAccessCorrectness(DatabaseContral &db){
    QFile file("test.dat");
    file.open(QIODevice::ReadOnly);
    QByteArray arr;
    char tmp[128];
    memset(tmp, 0x00, sizeof(tmp));
    auto count = file.read(tmp, sizeof(tmp) - 1);
    arr.append(tmp, static_cast<int>(count));
    qDebug()<<"read length: " << count << ", "<< arr.length();

    QString data = QString(arr.toHex());
    QString sql;
    QString tablename = "data_0001";
    QString time = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QString type = "RTCM3.2";
    QString mountpoint = "test1";

    sql = "insert into "+ tablename +"(DATE,DATATYPE,MOUNTPOINT,DATA) values('"+time+"','"+type+"','"+mountpoint+"','"+data+"');";
    qDebug() << "sql:" <<sql;
    auto ret = db.Ins_Del_Upd_Database(sql);
    if(ret){
        qDebug() << "insert into " << tablename << " successed";
        db.Commit();
    }else{
        qDebug() << "insert into " << tablename << " failed";
        return false;
    }

    //
    sql = "select DATA from " + tablename + " where MOUNTPOINT = " + "'" + mountpoint + "';";
    qDebug() << "sql:" <<sql;
    auto query = db.Select_Database(sql);
    if(query.next()){
        qDebug() << "select success";
        QString read_data = query.value("DATA").toString();
        QByteArray read_arr = QByteArray::fromHex(read_data.toUtf8());
        qDebug() << "length : " << arr.length() << ", " << read_arr.length();
        if(read_arr == arr){
            qDebug() << "数据相同 ";
        }else{
            qDebug() << "数据不同 ";
        }
    }
    return true;
}


int getCount(DatabaseContral &db){
    QString mount_point = "test1";
    QString sql = "select count(1) from `user` where MOUNTPOIONT = '" + mount_point + "';";;
    qDebug() << "sql:" << sql;
    auto query = db.Select_Database(sql);

    auto count = -1;
    if(query.next()){
        count = query.value(0).toInt();
        qDebug() << "count:" << count;
    }else{
        qDebug() << "select error";
    }

    return count;
}

int main(int argc,char *argv[])
{
    QCoreApplication a(argc,argv);
    DatabaseContral db;
    QString ip = "192.168.0.104";
    int port = 3306;
    QString data_base = "test";
    QString user = "root";
    QString password = "root";

    db.Connect_Database(ip, port, data_base, user, password);

//    QString select_str = "select * from data;";
//    auto result = db.Select_Database(select_str);
//    while (result.next()) {
//        qDebug() << result.value(0).toString();
//        qDebug() << result.value(1).toInt();
//    }

//    verifyHexDataAccessCorrectness(db);
    getCount(db);

    db.Disconnect_Database();

//    struct TT{
//        QString mount_point;
//        double x;
//        double y;
//        double z;
//    };
//    QMap<QString, struct TT> map;
    return a.exec();
}

//#include <QCoreApplication>
//#include <QSqlDatabase>
//#include <QSqlQuery>
//#include <QSqlError>
//#include <QtDebug>
//void connect_mysql()
//{
//    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
//       db.setHostName("192.168.0.27");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
//       db.setPort(3306);                 //连接数据库端口号，与设置一致
//        db.setDatabaseName("hwa_1");      //连接数据库名，与设置一致
//        db.setUserName("root");          //数据库用户名，与设置一致
//        db.setPassword("root");    //数据库密码，与设置一致
//        db.open();
//        if(!db.open())
//        {
//            qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
//            return ;
//        }
//        else
//        {
//             qDebug()<<"连接成功"<<"connect to mysql OK";
//        }
//        QSqlQuery query(db);
//        query.exec("select * from data");
//        while(query.next()){
//            qDebug()<<query.value("ip").toString();
//            qDebug()<<query.value("type").toString();
//        }
//}
//int main(int argc,char *argv[])
//{
//    QCoreApplication a(argc,argv);
//    connect_mysql();
//    return a.exec();
//}
