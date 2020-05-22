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
struct HandleRect
{
    HWND hwnd;
    RECT wndRect;
    HandleRect() {}
};

class ScreenUtil:public QObject
{
    Q_OBJECT
public:
    ScreenCaputredEvent *ScreenCaputred;
    QEvent *ScreenCaputreCancelled;
    HandleRect GetCursorPosWndRect(QPoint p);
    bool IsPointInRect(QPoint p,RECT t);
    void StartCaputre(int timeOutSeconds,QObject sender);
    void StartCaputre(int timeOutSeconds, QSize size);
    void OnScreenCaputred(QObject sender,RECT clipRegion);
    void OnScreenCaputreCancelled(QObject sender);
    void OnWaitTimmerTick(QObject sender,QEvent e);
    explicit ScreenUtil(QObject *parent = nullptr);
signals:
    void sendData(int,QSize);
private:
    RECT *waitRect;
    QTimer waitTimmer;
    QPoint *waitPoint;
    QObject *paramSender;
    QList<HandleRect> *hwndRectList;
    void InitWndHandleRect();
};

#endif // SCREENUTIL_H
