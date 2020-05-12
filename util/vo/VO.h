#ifndef VO_H
#define VO_H

#include <QObject>
#include "util/publicHelper.h"
#include <QJsonObject>
#include <QVariant>
#include <QHash>
#include <QMap>
#include <QInternal>
#include <QDebug>
#include <QVector>
//一般类型序列化的json
struct QjsonVector
{
   QString code;
   QString msg;
   QHash<QString,QVariant> data;
   void serializeFromJson(QJsonObject json){
      this->code=(PublicHelper::getJsonValue(json,"code")).toString();
      this->msg=(PublicHelper::getJsonValue(json,"msg")).toString();
      QJsonObject::Iterator it;
       for(it=json.begin();it!=json.end();it++){
           if(it.value().isObject()){
               QJsonObject d=it.value().toObject();
               data=d.toVariantHash();
           }
       };
   }
};

struct RestResult
{
   QString code;
   QString msg;
   QJsonObject data;
    void set(QJsonObject json){
      this->code=(PublicHelper::getJsonValue(json,"code")).toString();
      this->msg=(PublicHelper::getJsonValue(json,"msg")).toString();
      QJsonObject::Iterator it;
       for(it=json.begin();it!=json.end();it++){
           this->data.insert(it.key(),it.value());
       };
   }
};
class VO:public QObject
{
    Q_OBJECT
public:
    explicit VO(QObject *parent = nullptr);
};

#endif // VO_H
