
#include "HttpUtil.h"
#include <QDebug>
#include <QtNetwork/qnetworkreply.h>
#include <QUrl>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonDocument>
#include "util/publicHelper.h"
#include <QApplication>
#include <util/CodeConstants.h>
QString __url="";
QString username="";
HttpUtil::HttpUtil(QObject *parent):QObject(parent)
{
    m_network = new QNetworkAccessManager(this);
    QObject::connect(m_network, SIGNAL(finished(QNetworkReply*)),this ,SLOT(replyFinished(QNetworkReply*)));
    qDebug()<<SESSION;
}
void HttpUtil::get(QUrl(url),std::function<void(QJsonObject json)> call)
{

    HttpUtil::callBack= std::move(call);
    QString _url=QT_HOST+url.toString();
    QNetworkRequest request = QNetworkRequest(_url);

    request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
    request.setRawHeader("Cookie",("TICKETSESSIONSID="+SESSION).toLatin1());
    timer=new QElapsedTimer();
    timer->start();
    m_network->get(QNetworkRequest(request));

}

void HttpUtil::get(QUrl(url),QJsonObject *p,std::function<void(QJsonObject json)> call)
{
    __url=url.toString();
    HttpUtil::callBack= std::move(call);
    QString _url=QT_HOST+url.toString()+"?"+PublicHelper::parseQJsonObjectToQString(p);
    QNetworkRequest request = QNetworkRequest(QUrl(_url));
    request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
    request.setRawHeader("Cookies",("TICKETSESSIONSID="+SESSION).toLatin1());
    timer=new QElapsedTimer();
    timer->start();
    m_network->get(QNetworkRequest(request));

}

void HttpUtil::put(QUrl(url),QJsonObject *p, std::function<void(QJsonObject json)> call)
{

    callBack= std::move(call);
    QString _url=QT_HOST+url.toString();
    const QByteArray sb=PublicHelper::parseQJsonObjectToQByteArray(p);
    QString userName=PublicHelper::getJsonValue(*p,"userName");
    username=userName;
    QNetworkRequest request;
    request.setUrl(QUrl(_url));
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("Cookies",("TICKETSESSIONSID="+SESSION).toLatin1());
    request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
    timer=new QElapsedTimer();
    timer->start();
    m_network->put(QNetworkRequest(request),sb);

}

void HttpUtil::replyFinished(QNetworkReply *reply)
{
    timer->elapsed();
    QJsonObject jsonObject;
    QVariant var;
    QJsonValue value;
    cookieJar= this->m_network->cookieJar();
    QList<QNetworkCookie> list= cookieJar->cookiesForUrl(QUrl(QT_HOST));
    if(timer->hasExpired(qlonglong(NET_TIME_OUT))){
        QJsonObject res;
        res.insert("code",CODE_SYS_ERROR);
        res.insert("msg",CODE_SYS_ERROR_MSG);
        jsonObject= res;
    }
    else{
        QByteArray databuff = reply->readAll();
        jsonObject=PublicHelper::parseQByteArrayToQJsonObject(databuff);
        QString code=PublicHelper::getJsonValue(jsonObject,"code");
        if(code==CODE_SUCCESS){
           var.setValue(list[0].value());
           if(var.data()!=NULL){
               value=QJsonValue::fromVariant(var);
               jsonObject.insert(QString(u8"TICKETSESSIONSID"),value);
               SESSION=value.toString();
              }
        }
    }
    callBack(jsonObject);
    delete timer;
}

void HttpUtil::replyError(QNetworkReply::NetworkError *err)
{
    qDebug() << err;
}
HttpUtil::~HttpUtil(){
    delete caller;
    delete m_network;
    this->deleteLater();
}

