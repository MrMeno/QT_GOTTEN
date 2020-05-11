#include "./src/LoginWindow.h"
#include <QApplication>
#include <qfile.h>
#include <qdir.h>
#include <QDebug>
#include "util/publicHelper.h"
#include "util/HttpUtil.h"
#include "util/DataBase.h"
#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QCloseEvent>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(true);
    a.connect(&a,SIGNAL(lastWindowClosed()),&a,SLOT(quit()));
    /*创建本地数据库 */
     DataBase db;
    //链接数据库
     db.createConnection();
    //创建user表
     db.createTable();
     db.reset();
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



