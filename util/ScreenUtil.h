#ifndef SCREENUTIL_H
#define SCREENUTIL_H
#ifndef _UNICODE
#define _T(x) L ## x
#else
#define _T(x) (x)
#endif
#include <QObject>
#include <windows.h>
#include <winuser.h>
#include <QWidget>
#include <QTimer>
#include "util/ScreenCaputredEvent.h"
#include <QPoint>
class ScreenUtil:public QObject
{
    Q_OBJECT
public:
    explicit ScreenUtil(QObject *parent = nullptr);
signals:
    void sendData(int,QSize);
private:

};

#endif // SCREENUTIL_H
