#include "publicHelper.h"
#include <QDir>
#include <QJsonObject>
#include <QDebug>
#include <QJsonDocument>

PublicHelper::PublicHelper(QObject *parent):QObject(parent)
{

}
QStringList PublicHelper::getDirName(QString path)
{
   QDir dir(path);
   if (!dir.exists())
   {
       return QStringList("");
   }
   dir.setFilter(QDir::Files | QDir::NoSymLinks);
   QStringList filters;
   filters << "*.bmp" << "*.qss";
   dir.setNameFilters(filters);
   QStringList list = dir.entryList();
   if (list.count() <= 0)
   {
       return QStringList("");
   }
   return list;
}
QString PublicHelper::parseQJsonObjectToQString(QJsonObject *repData)
{
    //遍历json对象
    QJsonObject::Iterator its;
    QString str="";
    for(its=repData->begin();its!=repData->end();its++)
    {
         QString Value=its.value().toString();
         QString Key=its.key();
         str+="&"+Key+"="+Value;
    }
    str= str.right(str.length()-1);
    str.replace("\n","");
    return str;
}

QByteArray PublicHelper::parseQJsonObjectToQByteArray(QJsonObject *repData)
{
    QJsonDocument document=QJsonDocument(*repData);
    QByteArray array = document.toJson();// 转换成QByteArray
    return array;
}

PublicHelper::~PublicHelper()
{
    delete this;
}
