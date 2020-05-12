#define pragma execution_character_set("utf-8")
#ifndef HTTPUTIL_H
#define HTTPUTIL_H
#define QT_HOST "https://apitest.aibill.cn/api"
#define NET_TIME_OUT 6000
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <QtNetwork/qnetworkrequest.h>
#include <QUrl>
#include <util/CodeConstants.h>
#include <QElapsedTimer>
#include <QObject>
#include <QThread>
#include <functional>
#include <QMainWindow>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QCache>
#include "DataBase.h"
extern QString current_url;
class HttpUtil:public QObject
{
    Q_OBJECT
public:
     explicit HttpUtil(QObject *parent=nullptr);
     void  cookiesMangement();
     void  get( QUrl(url), std::function<void(QJsonObject json)> call);
     void  get(QUrl(url), QJsonObject *p, std::function<void(QJsonObject json)> call);
     void  post(QUrl(url),QJsonObject  *p, std::function<void(QJsonObject json)> call);
     void  put(QUrl(url), QJsonObject *p, std::function<void(QJsonObject json)> call);
     std::function<void(QJsonObject json)> callBack;
       //virtual QNetworkAccessManager *create(QObject *parent);
     ~HttpUtil();
signals:
     void finished(QNetworkReply *reply);
     void error(QNetworkReply::NetworkError);
public slots:
    void replyFinished(QNetworkReply *reply);
    void replyError(QNetworkReply::NetworkError *err);
private:
    QNetworkCookieJar *cookieJar;
    QElapsedTimer *timer;
    QMainWindow *caller;
    QNetworkAccessManager *m_network;
};
#endif // HTTPUTIL_H
