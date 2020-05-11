#include "DataBase.h"


DataBase::DataBase()
{
}
bool DataBase::createConnection()
{
    //以后就可以用"aibill"与数据库进行连接了
   QSqlDatabase db;
   if(db.contains("aibill")){
       db=QSqlDatabase::database("aibill");
   }
   else{

       db = QSqlDatabase::addDatabase("QSQLITE", "aibill");
   }
    db.setDatabaseName("ticket_abill.db");
    if( !db.open())
    {
        qDebug() << u8"DATABASE:error connect";
        return false;
    }
    qDebug() << u8"DATABASE:success connect";
    d_b=db;
    return true;
}

//创建数据库表
bool DataBase::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("aibill"); //建立数据库连接
    QSqlQuery query(db);
    bool success = query.exec("create table aibill_user(account varchar PRIMARY KEY,"
                              "create_time varchar,session_token varchar,isCurrent integer default 0)");
    //(id,account，create_time，session_token，isCurrent)
    if(success)
    {
       // qDebug() << u8"user create success";
        return true;
    }
    else
    {
        //QSqlError lastError = query.lastError();
       // qDebug() << u8"user create fail:"+lastError.driverText();
        return false;
    }
}

//向数据库中插入登录记录
bool DataBase::insert(QString account,QString token)
{
    QSqlDatabase db = QSqlDatabase::database("aibill"); //建立数据库连接
    QSqlQuery query(db);
    QString current_date_time =QDateTime::currentDateTime().toString();
    query.prepare("insert into aibill_user(account,session_token,create_time,isCurrent) values(:account,:session_token,:create_time,:isCurrent)");
    query.bindValue(":account",account);
    query.bindValue(":session_token",token);
    query.bindValue(":create_time",current_date_time);
    query.bindValue(":isCurrent",1);
    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() <<  u8"------------------insert error:"+lastError.driverText();
        return false;
    }
    qDebug() << u8"insert success-----------------------" ;
    return true;
}

//查询所有信息
bool DataBase::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database("aibill"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select * from aibill_user");
    QSqlRecord rec = query.record();
    qDebug() << QObject::tr(u8"aibill_user counter:" )+QString::number(rec.count());
    while(query.next())
    {
        for(int index = 0; index < rec.count(); index++)
          //  qDebug() << query.value(index) << "";
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
        qDebug() << u8"排序成功!";
        return true;
    }
    else
    {
        qDebug() << u8"排序失败！";
        return false;
    }
}

bool DataBase::reset(){
    QSqlDatabase db = QSqlDatabase::database("aibill"); //建立数据库连接
    QSqlQuery query(db);
    bool success=query.exec("update aibill_user set isCurrent=0");
    if(success)
    {
        //qDebug() <<QString::fromUtf8(u8"reset success");
        return true;
    }
    else
    {
       // qDebug() << QString::fromUtf8(u8"reset failed");
        return false;
    }
}
