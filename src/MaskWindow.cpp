#include "MaskWindow.h"
#include "ui_MaskWindow.h"
#include <QRect>
#include "util/ScreenUtil.h"
#include "CorePageWindow.h"
MaskWindow::MaskWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MaskWindow)
{
    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags()| Qt::WindowStaysOnTopHint);//
    this->setAttribute(Qt::WA_TranslucentBackground);
    int nWidth = GetSystemMetrics(SM_CXSCREEN);
    int nHeight = GetSystemMetrics(SM_CYSCREEN);
    this->setMinimumWidth(nWidth);
    this->setMinimumHeight(nHeight);
    ui->setupUi(this);
    this->setCursor(Qt::WhatsThisCursor);
    ScreenUtil *src=new ScreenUtil(this);
    this->setFocus();
    pIndow=parent;
    connect(src,SIGNAL(sendData(int,QSize)), this, SLOT(getData(int,QSize)));
   // connect(this,SIGNAL(mouseDoubleClickEvent(QMouseEvent *event)), this, SLOT(getDocument(QMouseEvent *event)));
}

void MaskWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    HWND deskHD=::GetDesktopWindow();//顶层蒙版的句柄
    HWND S=::GetWindow(deskHD,5);//顶层蒙版的句柄
     this->close();
    getDocument(S);
    CorePageWindow *cp=static_cast<CorePageWindow*>(pIndow);
    cp->setVisibility(true);

}
void MaskWindow::getData(int Second,QSize s){
    timeSecond=Second;
    size=s;

}
void MaskWindow::getDocument(HWND hwnd){
     HWND M=::GetWindow(hwnd,2);
     qDebug()<<(int)M;
}
MaskWindow::~MaskWindow()
{
    delete ui;
}
