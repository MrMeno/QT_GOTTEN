#include "./src/LoginWindow.h"
#include <QApplication>
#include <qfile.h>
#include <qdir.h>
#include <QDebug>
#include "util/publicHelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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

