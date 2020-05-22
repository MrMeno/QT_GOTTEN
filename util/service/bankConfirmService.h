#ifndef BANKCONFIRMSERVICE_H
#define BANKCONFIRMSERVICE_H
#ifndef _UNICODE
#define _T(x) L ## x
#else
#define _T(x) (x)
#endif
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


class bankConfirmService:public QObject
{
      Q_OBJECT
public:
    explicit bankConfirmService(QObject *parent = nullptr);
     void getHTMLDocument(HWND hwnd);
};

#endif // BANKCONFIRMSERVICE_H
