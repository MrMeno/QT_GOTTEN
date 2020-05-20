#include "ScreenUtil.h"

ScreenUtil::ScreenUtil(QObject *parent):QObject(parent)
{

}

void ScreenUtil::getHTMLDocument(HWND hwnd){
    LRESULT lRes;
    LPCSTR N="WM_HTML_GETOBJECT";
    UINT nMsg = ::RegisterWindowMessageA(N);
    ::SendMessageTimeout( hwnd, nMsg, 0L, 0L, SMTO_ABORTIFHUNG, 1000, (DWORD*)&lRes );
    HRESULT hr;
    QAxObject spDoc;
    HRESULT iResult=ObjectFromLresult(lRes,IID_IHTMLDocument2,0,(void**)&spDoc);

}
ScreenUtil::~ScreenUtil()
{
    delete this;
}
