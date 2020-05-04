#ifndef PUBLICHELPER_H
#define PUBLICHELPER_H
#include <QObject>
#include <QUrl>
#include <QByteArray>

 class PublicHelper:public QObject
{
    Q_OBJECT
public:
     explicit PublicHelper(QObject *parent = nullptr);
     QStringList getDirName(QString path);
     QString parseQJsonObjectToQString(QJsonObject *repData);
     QByteArray parseQJsonObjectToQByteArray(QJsonObject *repData);
    ~PublicHelper();
};

#endif // PUBLICHELPER_H
