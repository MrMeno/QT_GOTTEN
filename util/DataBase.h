#ifndef DATABASE_H
#define DATABASE_H
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QTextCodec>

class DataBase
{
public:
    DataBase();
    bool createConnection();  //创建一个连接
        bool createTable();       //创建数据库表
        bool insert(QString name,QString token);            //出入数据
        bool queryAll();          //查询所有信息
        bool updateByname(QString name);  //更新
        bool deleteByname(QString name);  //删除
        bool sortById();          //排序
        bool selectCurrentUser(int isCurrent);
};

#endif // DATABASE_H
