#ifndef DLLHELPER_H
#define DLLHELPER_H
#ifdef _EXPORTING
#define API_DECLSPEC    __declspec(dllexport)
#else
#define API_DECLSPEC    __declspec(dllimport)
#endif

#include <windows.h>
#include <winuser.h>

//extern WINUSERAPI HWND GetDesktopWindow(void);

class DllHelper
{
public:

    DllHelper();

};

#endif // DLLHELPER_H
