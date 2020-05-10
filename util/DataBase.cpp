#include "DataBase.h"


DataBase::DataBase()
{
}
bool DataBase::createConnection()
{
    //以后就可以用"sqlite1"与数据库进行连接了
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "aibill");
    db.setDatabaseName("ticket_abill.db");
    if( !db.open())
    {
        qDebug() << u8"error connect";
        return false;
    }
    qDebug() << u8"success connect";
    return true;
}

//创建数据库表
bool DataBase::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("aibill"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table aibill_user(id integer PRIMARY KEY autoincrement,account varchar(100) PRIMARY KEY,"
                              "create_time varchar(100),session_token varchar(100),isCurrent int default 0)");
    //(id,用户名，登录时间，token，当前是否登录)
    if(success)
    {
        qDebug() << u8"user create success";
        return true;
    }
    else
    {
        qDebug() << u8"user create fail";
        return false;
    }
}

//向数据库中插入登录记录
bool DataBase::insert(QString account,QString token)
{
    QSqlDatabase db = QSqlDatabase::database("aibill"); //建立数据库连接
    QSqlQuery query(db);
    QString current_date_time =QDateTime::currentDateTime().toString();
    query.prepare("insert into aibill_user values(?, ?, ?, ?,?)");
    query.bindValue(1, account);
    query.bindValue(2, current_date_time);
    query.bindValue(3, token);
    query.bindValue(4, 1);
    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("insert error"));
        return false;
    }
    return true;
}

//查询所有信息
bool DataBase::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database("aibill"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select * from aibill_user");
    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("aibill_user counter：" ) << rec.count();
    while(query.next())
    {
        for(int index = 0; index < rec.count(); index++)
            qDebug() << query.value(index) << "";
        qDebug() << "\n";
    }
    return true;
}

//根据ID删除记录
bool DataBase::deleteByname(QString username)
{
    QSqlDatabase db = QSqlDatabase::database("aibill"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString("delete from aibill_user where account = %1").arg(username));
    if(!query.exec())
    {
        qDebug() << "删除记录失败！";
        return false;
    }
    qDebug() << "删除记录成功！";
    return true;
}

//根据username更新历史记录
bool DataBase::updateByname(QString account)
{
    QSqlDatabase db = QSqlDatabase::database("aibill"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString("update aibill_user set isCurrent=? where account=%1").arg(account));
    query.bindValue(0,0);
     bool success=query.exec();
     if(!success)
     {
          QSqlError lastError = query.lastError();
          qDebug() << lastError.driverText() << QString(QObject::tr("更新失败"));
     }
     qDebug() << "更新成功";
    return true;
}
//根据username更新历史记录
bool DataBase::selectCurrentUser(int isCurrent)
{
    QSqlDatabase db = QSqlDatabase::database("aibill"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString("select token from aibill_user set  where isCurrent=%1").arg(isCurrent));
    bool success=query.exec();
     if(!success)
     {
          QSqlError lastError = query.lastError();
          qDebug() << lastError.driverText() << QString(QObject::tr("查询失败"));
     }
     qDebug() << "查询成功";
    return true;
}


//排序
bool DataBase::sortById()
{
    QSqlDatabase db = QSqlDatabase::database("aibill"); //建立数据库连接
    QSqlQuery query(db);
    bool success=query.exec("select * from aibill_user order by id desc");
    if(success)
    {
        qDebug() << QObject::tr("排序成功");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("排序失败！");
        return false;
    }
}
