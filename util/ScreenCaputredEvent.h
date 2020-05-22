#ifndef SCREENCAPUTREDEVENT_H
#define SCREENCAPUTREDEVENT_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <windows.h>
static const QEvent::Type ScreenCaputredEventType = (QEvent::Type)QEvent::registerEventType(QEvent::User+100);
class ScreenCaputredEvent:public QEvent
{
public:
    ScreenCaputredEvent(Type ScreenCaputredEventType);
};


//信使
class ScreenCaputredEventSender: public QCoreApplication
{
public:
    ScreenCaputredEventSender(int argc,char *argv[]);

public:
    bool notify(QObject *receiver, QEvent *event);
};


//参数集合
class ScreenCaputredEventArgs: public QObject
{
public:
    void ScreenCaputredEventHandler(QEvent *event);
    bool event(QEvent *event);
    HWND hwnd;
    long int pointx;
    long int pointy;
};

//监控者
class ScreenCaputredEventWatcher: public QObject
{
public:
    bool eventFilter(QObject *watched, QEvent *event);
};




#endif // SCREENCAPUTREDEVENT_H
