
#include "HttpUtil.h"
#include <QDebug>
#include <QtNetwork/qnetworkreply.h>
#include <QUrl>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonDocument>
#include "util/publicHelper.h"
#include <QApplication>

QString __url="";
QString username="";
HttpUtil::HttpUtil(QObject *parent):QObject(parent)
{
    m_network = new QNetworkAccessManager(this);
    QObject::connect(m_network, SIGNAL(finished(QNetworkReply*)),this ,SLOT(replyFinished(QNetworkReply*)));
}
void HttpUtil::get(QUrl(url),std::function<void(QJsonObject json)> call)
{
    HttpUtil::callBack= std::move(call);
    QString _url=QT_HOST+url.toString();
    QNetworkRequest request = QNetworkRequest(_url);
    request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
    timer=new QElapsedTimer();
    timer->start();
    m_network->get(QNetworkRequest(request));

}

void HttpUtil::get(QUrl(url),QJsonObject *p,std::function<void(QJsonObject json)> call)
{
    HttpUtil::callBack= std::move(call);
    QString _url=QT_HOST+url.toString()+PublicHelper::parseQJsonObjectToQString(p);
    QNetworkRequest request = QNetworkRequest(QUrl(_url));
    request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
    timer=new QElapsedTimer();
    timer->start();
    m_network->get(QNetworkRequest(request));

}

void HttpUtil::put(QUrl(url),QJsonObject *p, std::function<void(QJsonObject json)> call)
{
    __url=url.toString();
    callBack= std::move(call);
    QString _url=QT_HOST+url.toString();
    const QByteArray sb=PublicHelper::parseQJsonObjectToQByteArray(p);
    QString userName=PublicHelper::getJsonValue(*p,"userName");
    username=userName;
    QNetworkRequest request;
    request.setUrl(QUrl(_url));
    request.setRawHeader("Content-Type","application/json");
    request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
    timer=new QElapsedTimer();
    timer->start();
    m_network->put(QNetworkRequest(request),sb);

}

void HttpUtil::replyFinished(QNetworkReply *reply)
{
    timer->elapsed();
    QJsonObject jsonObject;
    cookieJar= this->m_network->cookieJar();
    QList<QNetworkCookie> list= cookieJar->cookiesForUrl(QUrl(QT_HOST));
    for(int i=0;i<list.length();i++)
    {
        qDebug()<<list[i].name()<<":"<<list[i].value();
    };
    if(timer->hasExpired(qlonglong(NET_TIME_OUT))){
        QJsonObject res;
        res.insert("code",CODE_SYS_ERROR);
        res.insert("msg",CODE_SYS_ERROR_MSG);
        jsonObject= res;
    }
    else{
        QByteArray databuff = reply->readAll();
        jsonObject=PublicHelper::parseQByteArrayToQJsonObject(databuff);
        QString current_date_time =QDateTime::currentDateTime().toString();
        if(__url=="/login"){
            QSqlDatabase db = QSqlDatabase::database("aibill");
            QSqlQuery sql;
            bool hasThisUser=sql.exec("select * from aibill_user where account=\'"+username+"\'");
            if(hasThisUser){
                qDebug()<<username;
            }
            else{

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

