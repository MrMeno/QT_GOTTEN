#ifndef PUBLICHELPER_H
#define PUBLICHELPER_H
#include <QObject>
#include <QUrl>
#include <QByteArray>
#include <QTextCodec>
 class PublicHelper:public QObject
{
    Q_OBJECT
public:
    explicit PublicHelper(QObject *parent = nullptr);
    static QStringList getDirName(QString path);
    static QString parseQJsonObjectToQString(QJsonObject *repData);
    static QByteArray parseQJsonObjectToQByteArray(QJsonObject *repData);
    static QJsonObject parseQByteArrayToQJsonObject(QByteArray arr);
    static QString getJsonValue(QJsonObject json,QString name);
    ~PublicHelper();
};

#endif // PUBLICHELPER_H
