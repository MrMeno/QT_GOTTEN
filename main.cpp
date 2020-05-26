#include "./src/LoginWindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <qfile.h>
#include <qdir.h>
#include <QDebug>
#include "util/publicHelper.h"
#include "util/HttpUtil.h"
#include "util/DataBase.h"
#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QCloseEvent>
#include <QStringList>
#include <QtFontDatabaseSupport/QtFontDatabaseSupport>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
    //a.connect(&a,SIGNAL(lastWindowClosed()),&a,SLOT(quit()));
    /*创建本地数据库 */
  //   DataBase db;
    //链接数据库
  //   db.createConnection();
    //创建user表
 //    db.createTable();
  //   db.reset();
     /*加载字体*/
    QString dir = QCoreApplication::applicationDirPath();
    QStringList fontList;
    fontList.clear();
    int aiFontId = QFontDatabase::addApplicationFont(":/font/HanSans.ttf");
    if (aiFontId != -1) // -1为加载失败
    {
        fontList << QFontDatabase::applicationFontFamilies(aiFontId);
    }
    qDebug()<<"family"<<QFontDatabase::applicationFontFamilies(aiFontId);
    if (!fontList.isEmpty())
    {
        QFont font;
        font.setFamily(fontList.at(0));
        QApplication::setFont(font);
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



