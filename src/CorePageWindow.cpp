#include "CorePageWindow.h"
#include "ui_CorePageWindow.h"
#include <QApplication>
#include <qfile.h>
#include <qgraphicseffect.h>
#include <QMessageBox>
#include <QJsonObject>
#include <iterator>
#include <qdebug.h>
#include "util/httpService.h"
#include <QRegExp>
#include <QValidator>
#include "util/DataBase.h"
#include <QIcon>

CorePageWindow::CorePageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CorePageWindow)
{
    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags()|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(10);	//设置圆角半径 像素
    shadowEffect->setColor(Qt::black);	// 设置边框颜色
    shadowEffect->setOffset(0);
    ui->list_top=new drag_win_widget(parent);
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/logo.png"));
    ui->content_core_frame->setGraphicsEffect(shadowEffect);
    httpService *serve=new httpService();
    QJsonObject *param =new QJsonObject();
    param->insert("pageNo","1");
     param->insert("pageSize","10");
     serve->getBillList(param,[=](QJsonObject res){

     });
}

void CorePageWindow::resizeEvent(QResizeEvent *event){
    QSize size=this->size();
    ui->content_core_frame->resize(size.width(),size.height()-40);
    QSize frame_size=ui->content_core_frame->size();
    ui->list_content->resize(frame_size.width(),frame_size.height()-200);
}
CorePageWindow::~CorePageWindow()
{
    delete ui;
}
