#include "MaskWindow.h"
#include "ui_MaskWindow.h"

MaskWindow::MaskWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MaskWindow)
{
    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags()| Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QSize winSize=QApplication::desktop()->size();
    this->resize(winSize.width(),winSize.height());
    ui->setupUi(this);
    this->setCursor(Qt::WaitCursor);

}

MaskWindow::~MaskWindow()
{
    delete ui;
}
