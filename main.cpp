
#include "./src/LoginWindow.h"
#include <QApplication>
#include <qfile.h>
#include <qdir.h>
#include <QDebug>
#include "util/publicHelper.h"
#include "util/HttpUtil.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
    /*创建本地数据库*/
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("ticket_abill.db");
    //链接数据库
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }
    //创建user表
    QSqlQuery sql_query;
    if(!sql_query.exec("create table user(username text primary key, token text,isCurrent int default 0,login_time text)"))
    {
        qDebug() << "Error: Fail to create table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "user created!";
    }
    /*加载样式表*/
    PublicHelper *helper=new PublicHelper();
    QStringList strList=helper->getDirName(":/qss");
    QString styleSheet="";
    for(int i=0;i<strList.length();i++){
        QFile file(":/qss/"+strList[i]);
        if(file.open(QFile::ReadOnly))
           {
                 styleSheet += QLatin1String(file.readAll());
                file.close();
           }
      }
    a.setStyleSheet(styleSheet);
    LoginWindow w;
     w.show();
    return a.exec();
}



