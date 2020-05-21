#ifndef SCREENUTIL_H
#define SCREENUTIL_H
#include <QObject>
#include <windows.h>
#include <winuser.h>
#include <oleacc.h>
#include <initguid.h>
#include <oleauto.h>
#include <comdef.h>
#include <shobjidl.h>
#include <QWidget>
#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxBase>
#include <ActiveQt/QAxObject>
#include <ActiveQt/ActiveQtDepends>
#include <mshtml.h>
#include "util/shdocvw.h"
#include <comdef.h>

class ScreenUtil:public QObject
{
    Q_OBJECT
public:
   explicit ScreenUtil(QObject *parent = nullptr);
  void getHTMLDocument(HWND hwnd);
};

#endif // SCREENUTIL_H
