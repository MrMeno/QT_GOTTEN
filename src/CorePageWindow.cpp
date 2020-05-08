#include "CorePageWindow.h"
#include "ui_CorePageWindow.h"
#include <QApplication>
#include <qfile.h>
#include <qgraphicseffect.h>
#include <windows.h>
#include <QMessageBox>
#include <QObject>
#include <QJsonObject>
#include <iterator>
#include <qdebug.h>
#include "util/HttpUtil.h"
#include <QRegExp>
#include <QValidator>

CorePageWindow::CorePageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CorePageWindow)
{
    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags()| Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(10);	//设置圆角半径 像素
    shadowEffect->setColor(Qt::black);	// 设置边框颜色
    shadowEffect->setOffset(0);
    ui->setupUi(this);
     ui->content_core_frame->setGraphicsEffect(shadowEffect);
}

void CorePageWindow::resizeEvent(QResizeEvent *event){
    QSize size=this->size();
    ui->content_core_frame->resize(size.width(),size.height());
    ui->list_content->resize(size.width(),size.height()-200);
}
CorePageWindow::~CorePageWindow()
{
    delete ui;
}
