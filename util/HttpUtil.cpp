
#include "HttpUtil.h"
#include <QDebug>
#include <QtNetwork/qnetworkreply.h>
#include <QUrl>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonDocument>
#include "util/publicHelper.h"
#include <QApplication>

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
      timer->start();
      m_network->get(QNetworkRequest(request));

}

 void HttpUtil::get(QUrl(url),QJsonObject *p,std::function<void(QJsonObject json)> call)
{
     HttpUtil::callBack= std::move(call);
     PublicHelper *helper=new PublicHelper();
      QString _url=QT_HOST+url.toString()+helper->parseQJsonObjectToQString(p);
      QNetworkRequest request = QNetworkRequest(QUrl(_url));
      request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
      timer->start();
      m_network->get(QNetworkRequest(request));

}

  void HttpUtil::put(QUrl(url),QJsonObject *p, std::function<void(QJsonObject json)> call)
{
      callBack= std::move(call);
      QString _url=QT_HOST+url.toString();
      PublicHelper *helper=new PublicHelper();
      const QByteArray sb=helper->parseQJsonObjectToQByteArray(p);
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
    PublicHelper *helper=new PublicHelper();
    QJsonObject jsonObject;
    if(timer->hasExpired(qlonglong(NET_TIME_OUT))){
         QJsonObject res;
         res.insert("code",CODE_SYS_ERROR);
         res.insert("msg",CODE_SYS_ERROR_MSG);
         jsonObject= res;
    }
   else{
        QByteArray databuff = reply->readAll();
        jsonObject=helper->parseQByteArrayToQJsonObject(databuff);
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

