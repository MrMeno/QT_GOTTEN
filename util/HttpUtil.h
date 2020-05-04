#define pragma execution_character_set("utf-8")
#ifndef HTTPUTIL_H
#define HTTPUTIL_H
#define QT_HOST "https://apitest.aibill.cn/api"
#define NET_TIME_OUT 60
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QUrl>
#include <util/CodeConstants.h>
#include <QElapsedTimer>

 class HttpUtil:public QObject
{
     Q_OBJECT
public:
      HttpUtil(QObject *parent = nullptr);
     QString parseQJsonObject(QJsonObject *json);
     QString  get( QUrl(url));
     QString  get(QUrl(url), QJsonObject *p);
     QString  post(QUrl(url),QJsonObject  *p);
     QJsonObject  put(QUrl(url), QJsonObject *p);
     ~HttpUtil();
signals:
     void finished(QNetworkReply *reply);
     void error(QNetworkReply::NetworkError err);
public slots:
    void replyFinished(QNetworkReply *reply);
    void replyError(QNetworkReply::NetworkError);
private:
    QNetworkAccessManager *m_network;
    QElapsedTimer *timer;


};
#endif // HTTPUTIL_H
