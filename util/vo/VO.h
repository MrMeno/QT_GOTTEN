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
/*template<typename T>
class RestResult
{
public:
    QString code;
    QString msg;
    T data;

};
template<class PageListVO>
class BillPageListVO{
    public:
     PageListVO page;
};

template<class BillListInfo>
class PageListVO{
    public:
    QString firstPage;
    QString lastPage;
    QString nextPage ;
    QString pageNo ;
    QString pageSize;
    QString prePage;
    QList<BillListInfo> result;
    QString sidx ;
    QString totalCount ;
    QString totalPages ;
};
template<class BillListExVO>
class BillListInfo{
    public:
    QString id;
    QString billNo;
    QString billMedia ;
    QString billAmountLower ;
    QString dueDate;
    QString endorsor;
    QString picFrontUrl;
    QString picBackUrl ;
    QString isException ;
    QString exceptionStatus ;

    QString ticketSource;
    QString showErr;
    QString isBackException ;
    QString isFrontException ;
    QString endorseTotalCount;
    QString version;
    QString acceptName;
    QList<BillListExVO> exceptionList;
};
class BillListExVO{
    public:
    QString exceDictKey;
    QString exceDictValue;
    QString count;
    QString seqNo;
};*/

class VO:public QObject
{
    Q_OBJECT
public:
    explicit VO(QObject *parent = nullptr);
};

#endif // VO_H
