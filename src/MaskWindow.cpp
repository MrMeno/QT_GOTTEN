#include "MaskWindow.h"
#include "ui_MaskWindow.h"
#include <QRect>
#include "util/ScreenUtil.h"

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
    this->setCursor(Qt::PointingHandCursor);
    ScreenUtil *src=new ScreenUtil(this);
    connect(src,SIGNAL(sendData(int,QSize)), this, SLOT(getData(int,QSize)));
}

void MaskWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    HWND maskHd=::FindWindow(NULL,L"MaskWindow");
    RECT RECTs;
    HWND S=::GetDesktopWindow();
    ::GetWindowRect(S,&RECTs);
}
void MaskWindow::getData(int Second,QSize s){
    timeSecond=Second;
    size=s;
}
MaskWindow::~MaskWindow()
{
    delete ui;
}
