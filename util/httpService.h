#ifndef HTTPSERVICE_H
#define HTTPSERVICE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "HttpUtil.h"
#include "CodeConstants.h"
#include "publicHelper.h"
#include <functional>
#include <QObject>
#include <QJsonObject>
class httpService:public QObject
{
    Q_OBJECT
public:
    httpService(QObject *parent=nullptr);
    HttpUtil *http;
    void login (QJsonObject *LoginDTO,std::function<void(QJsonObject json)> call);
};

#endif // HTTPSERVICE_H
