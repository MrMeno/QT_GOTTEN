#define pragma execution_character_set("utf-8")
#ifndef CODEHELPER_H
#define CODEHELPER_H
#define CODE_SUCCESS "000000"
#define CODE_SERVER_ERR "010001"
#define CODE_PSW_OUTDATE "010011"
#define CODE_BILL_FRONT_EXIST "020001"
#define CODE_BILL_BACK_EXIST "020002"
#define CODE_NO_LOGIN "990010"
#define CODE_SYS_ERROR "999999"
#define CODE_SYS_ERROR_MSG "网络异常"
#define CODE_USER_KICK_OUT "010005"
#define CODE_UPLOAD_DUPLICATE "080103"
#define CODE_USER_UN_AUTHORIZED "010003"

#include <QObject>
#include "util/publicHelper.h"
#include <QJsonObject>
#include <QVariant>
#include <QHash>
#include <QMap>
#include <QInternal>
#include <QDebug>
#include <QVector>
#include "util/vo/VO.h"
extern QString SESSION;
extern QString USERID;
extern QString ORGSHORTNAME;
extern QString ORGNAME;
extern QString INVITEURL;
extern QString USERNAME;
//储存一般化的json数据,不超过两层数据结构


class CodeHelper:public QObject
{
    Q_OBJECT

public:
    explicit CodeHelper(QObject *parent = nullptr);
    static QString API_HEARTBEAT;
    static QString API_LOGIN;
    static QString API_CHANGE_PSW;
    static QString API_GET_BANK_DOMAIN;
    static QString API_GET_RECEIOT_BANK_DOMAIN;
    static QString API_LOGOUT;
    static QString API_GET_ORG;
    static QString API_BILL_UPLOAD;
    static QString API_RECEIPT_UPLOAD;
    static QString API_BILL_LIST;
    static QString API_BILL_UPDATE;
    static QString API_BILL_DETAIL;
    static QString API_RECEIPT_DETAIL;
    static QString API_BILL_REFUSE;
    static QString API_APP_INFO;
    static QString API_LIST_PAGE;
    static QString API_LIST_RECIPT;
    static QString API_POST_EXCEPTION;
    static QString API_GET_ACCOUNT;
    static QString API_ACCOUNT_UPLOAD;
    static QString API_PUBLISH_INIT;
    static QString API_PUBLISH_UPLOAD;
    static QString API_PUBLISH_ACCOUNTLIST;
    ~CodeHelper();
};

#endif // CODEHELPER_H
