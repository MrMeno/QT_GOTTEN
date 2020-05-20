#ifndef SCREENUTIL_H
#define SCREENUTIL_H
#include <QObject>
#include <windows.h>
#include <winuser.h>
#include <oleacc.h>
#include <oleauto.h>
#include <comdef.h>
#include <shobjidl.h>
#include <QWidget>
#include <ActiveQt/QAxWidget>
#include <ActiveQt/qaxbase.h>
#include <ActiveQt/QAxObject>
#include <mshtml.h>

class ScreenUtil:public QObject
{
    Q_OBJECT
public:
   explicit ScreenUtil(QObject *parent = nullptr);
  void getHTMLDocument(HWND hwnd);
    ~ScreenUtil();
};

#endif // SCREENUTIL_H
