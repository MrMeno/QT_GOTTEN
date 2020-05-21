#include "ScreenUtil.h"
//typedef _com_ptr_t <_com_IIID<IHTMLDocument2, &__uuidof(IHTMLDocument2)>> IHTMLDocument2Ptr;
_COM_SMARTPTR_TYPEDEF(IHTMLDocument2, IID_IHTMLDocument2);
_COM_SMARTPTR_TYPEDEF(IHTMLElement, IID_IHTMLElement);
ScreenUtil::ScreenUtil(QObject *parent):QObject(parent)
{

}

void ScreenUtil::getHTMLDocument(HWND hwndIE){
    CoInitialize(NULL);
    IHTMLDocument2Ptr pDoc2;
    QString strTemp="";
    LPCWSTR LIBS= _T("OLEACC.DLL");
    HINSTANCE hinst=::LoadLibrary(LIBS);
    if(hinst!=NULL) {
    LRESULT lres;
    UINT unMsg=::RegisterWindowMessage("WM_HTML_GETOBJECT");
    ::SendMessageTimeout(hwndIE,unMsg,0L,0L,SMTO_ABORTIFHUNG,1000,(DWORD*)&lres);
    LPFNOBJECTFROMLRESULT pfObjectFromLresult=(LPFNOBJECTFROMLRESULT)::GetProcAddress(hinst,"ObjectFromLresult");
    if(pfObjectFromLresult!=NULL) {
    HRESULT hres;
    hres=(*pfObjectFromLresult)(lres,IID_IHTMLDocument2,0,(void**)&pDoc2);
    if(SUCCEEDED(hres)) {
    IHTMLElementPtr pHtmlElem;
    hres=pDoc2->get_body(&pHtmlElem);
    BSTR bstrText=NULL;
    pHtmlElem->get_innerText(&bstrText);
    _bstr_t _bstrTemp(bstrText,false);
    //strTemp=(char*)_bstr_t(bstrText);
    strTemp=(char*)_bstrTemp;
    }
    }
    ::FreeLibrary(hinst);
    }
    CoUninitialize();
    CoInitialize(NULL);
   /* QAxWidget *webWidget=new QAxWidget();
    webWidget->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));
    char *output = NULL;
    QAxObject *document = webWidget->querySubObject("Document");
    if(document){
        IHTMLDocument2 *doc2 = nullptr;
        document->queryInterface(QUuid(IID_IHTMLDocument2), (void**)&doc2);
        if (doc2)
        {
            IPersistStreamInit *pPSI=NULL;
            IStream *pStream=NULL;
            HGLOBAL hHTMLText;
            if (SUCCEEDED(doc2->QueryInterface(&pPSI)))
            {
                const int MaxBuffSize =64*1024;
                hHTMLText = GlobalAlloc(GMEM_FIXED, MaxBuffSize);
                CreateStreamOnHGlobal(hHTMLText, TRUE, &pStream);
                pPSI->Save(pStream, FALSE);
                LARGE_INTEGER li;
                li.QuadPart = 0;
                pStream->Seek(li,0,NULL);
                output = new char[MaxBuffSize];
                output[MaxBuffSize-1] = 0;
                ULONG readed = 0;
                pStream->Read((void*)output,MaxBuffSize-1,&readed);
                output[readed] = 0;
                pStream->Release();
                //GlobalFree(hHTMLText);
                pPSI->Release();
            }
            doc2->Release();
        }
    }
    if(output)
    {
        qDebug()<<QString::fromUtf8(output);

        delete[] output;
    }
    else
    {
        qDebug()<<QString::fromUtf8("control fail");
    }*/
}

