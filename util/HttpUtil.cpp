
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
       QObject::connect(HttpUtil::m_network, SIGNAL(finished(QNetworkReply*)),this ,SLOT(replyFinished(QNetworkReply*)));
}
 QString HttpUtil::get(QUrl(url))
{      QString _url=QT_HOST+url.toString();
      QNetworkRequest request = QNetworkRequest(_url);
      request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
      m_network->get(QNetworkRequest(request));
         QNetworkReply *res=  m_network->get(QNetworkRequest(request));
         QByteArray databuff = res->readAll();
         QString result = QString::fromStdString(databuff.toStdString()).toUtf8();
       return result;
}

 QString HttpUtil::get(QUrl(url),QJsonObject *p)
{
      PublicHelper *helper=new PublicHelper(this);
      QString _url=QT_HOST+url.toString()+helper->parseQJsonObjectToQString(p);
      QNetworkRequest request = QNetworkRequest(QUrl(_url));
      request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
      QNetworkReply *res=  m_network->get(QNetworkRequest(request));
      QByteArray databuff = res->readAll();
      QString result = QString::fromStdString(databuff.toStdString()).toUtf8();
    return result;
}

 QJsonObject HttpUtil::put(QUrl(url),QJsonObject *p)
{
      QString _url=QT_HOST+url.toString();
      PublicHelper *helper=new PublicHelper(this);
      const QByteArray sb=helper->parseQJsonObjectToQByteArray(p);
      QNetworkRequest request;
      request.setUrl(QUrl(_url));
      request.setRawHeader("Content-Type","application/json");
      request.setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.76 Mobile Safari/537.36"));
      timer=new QElapsedTimer();
      timer->start();
      QNetworkReply *res=  m_network->put(QNetworkRequest(request),sb);
      timer->elapsed();
      if(timer->hasExpired(qlonglong(NET_TIME_OUT))){
           QJsonObject jsonObject;
           jsonObject.insert("code",CODE_SYS_ERROR);
           jsonObject.insert("msg",CODE_SYS_ERROR_MSG);
           return jsonObject;
      }
     else{
          QByteArray databuff = res->readAll();
          QString result = QString(databuff);
          QJsonDocument jsonDocument = QJsonDocument::fromJson(result.toUtf8().data());
          QJsonObject jsonObject = jsonDocument.object();
          return jsonObject;
      }
}

void HttpUtil::replyFinished(QNetworkReply *reply)
{
    QByteArray databuff = reply->readAll();
    QString result = QString(databuff);
    QJsonDocument jsonDocument = QJsonDocument::fromJson(result.toUtf8().data());
    QJsonObject jsonObject = jsonDocument.object();
   // qDebug() << jsonObject;
}

void HttpUtil::replyError(QNetworkReply::NetworkError err)
{
      // qDebug() << err;
}
HttpUtil::~HttpUtil(){
  this->deleteLater();
}

