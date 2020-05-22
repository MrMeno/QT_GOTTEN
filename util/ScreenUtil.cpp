#include "ScreenUtil.h"
#include "src/MaskWindow.h"
ScreenUtil::ScreenUtil(QObject *parent):QObject(parent)
{

}


ScreenUtil::GetCursorPosWndRect(QPoint p){
    HandleRect *reshdlRect = new HandleRect();
    reshdlRect->hwnd = 0;
    foreach (auto element,hwndRectList)
    {
        HandleRect element_= qobject_cast<HandleRect *>(element);
        if (IsPointInRect(p, element_.wndRect))
        {
            reshdlRect = element_;
            return reshdlRect;
        }
    }
}

bool ScreenUtil::IsPointInRect(QPoint pt,RECT rt){
    long reWidth=rt.right-rt.left;
    long reHeight=rt.bottom-rt.top;
    if (pt.x() >= rt.left && pt.y() >= rt.top&& pt.x() <= rt.left + reWidth &&pt.y()<= rt.top + reHeight)
    {
        return true;
    }
    else
        return false;
}

void ScreenUtil::InitWndHandleRect(){
    hwndRectList->clear();
    HandleRect *hdlRect = new HandleRect();
    hdlRect->hwnd = ::GetDesktopWindow();
    RECT rc;
    hdlRect->hwnd = ::GetWindow(hdlRect->hwnd, 5);
    while ((int)(hdlRect->hwnd)!= 0)
    {
        ::GetWindowRect(hdlRect->hwnd,&rc);
        if (IsWindowVisible(hdlRect->hwnd))
        {
            hdlRect->wndRect = new RECT(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
            hwndRectList->append(hdlRect);
        }
        hdlRect->hwnd = GetWindow(hdlRect->,2);
    }
}


ScreenUtil::StartCaputre(int timeOutSeconds,QObject sender){
    paramSender = sender;
    StartCaputre(timeOutSeconds, NULL);
}


ScreenUtil::StartCaputre(int timeOutSeconds,QSize *size){
    InitWndHandleRect();
    MaskWindow *mask = new MaskWindow(this);
    emit sendData(timeOutSeconds,size);
    mask->show();
}


ScreenUtil::OnScreenCaputred(QObject sender, RECT clipRegion){
    int sWidth=(int)(clipRegion.right-clipRegion.left)/2;
    int sHeight=(int)(clipRegion.bottom-clipRegion.top)/2;
    if (ScreenCaputred != null)
    {
        waitPoint = new QPoint((int)(clipRegion.left + sWidth),(int)(clipRegion.top + sHeight));
        waitRect = clipRegion;
        if (waitTimmer == NULL)
        {
            waitTimmer = new QTimer();
        }
        waitTimmer.setInterval(300);
        waitTimmer.Start();
    }
}

void ScreenUtil::OnWaitTimmerTick(QObject sender,QEvent e){
    waitTimmer.stop();
    HWND handel = ::WindowFromPoint(waitPoint);
    ScreenCaputred(sender,new ScreenCaputredEventArgs(handel, paramSender));
}

void ScreenUtil::OnScreenCaputreCancelled(QObject sender){
    if (ScreenCaputreCancelled != NULL)
    {
        ScreenCaputreCancelled(sender,NULL);

    }
}
