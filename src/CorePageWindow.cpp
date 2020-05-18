#include "CorePageWindow.h"
#include "ui_CorePageWindow.h"
#include <QApplication>
#include <qfile.h>
#include <qgraphicseffect.h>
#include <QMessageBox>
#include <QJsonObject>
#include <qdebug.h>
#include "util/httpService.h"
#include <QScrollArea>
#include <QPainter>
#include "components/bill_list_widget.h"
#include <QLayout>
CorePageWindow::CorePageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CorePageWindow)
{
    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags()|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
    this->pageNo=1;
    this->pageSize=5;
    this->setStatusBar(ui->statusBar);
    topInit();
    getListPage();
}
/*
 * @
   头部初始化
*/
void CorePageWindow::topInit(){
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(10);	//设置圆角半径 像素
    shadowEffect->setColor(Qt::black);	// 设置边框颜色
    shadowEffect->setOffset(0);
    ui->content_core_frame->setGraphicsEffect(shadowEffect);
    QGridLayout *topLayout=new QGridLayout(this);
   // QLabel *imgLabel=new QLabel();
   // imgLabel.setPixmap();
   // topLayout->addItem(logo,1,1,1,1,Qt::AlignLeft);
    ui->list_top->setLayout(topLayout);
}
/*
 * @
   获取列表数据
*/
void CorePageWindow::getListPage(){
    httpService *serve=new httpService();
    QJsonObject *param =new QJsonObject();

    param->insert("pageNo",QString::number(pageNo));
    param->insert("pageSize",QString::number(pageSize));
    serve->getBillList(param,[=](QByteArray arr){
        QString str(arr);
        QScriptEngine engine;
        QScriptValue value=engine.evaluate("json="+str);
        QScriptValue code=value.property("code");
        if(code.toString()==CODE_SUCCESS){
            QScriptValue res_data=value.property("data");
            QScriptValue res_page=res_data.property("page");
            QScriptValue res_re=res_page.property("result");
            QList<QVariant> listData=  res_re.toVariant().toList();
            bill_list_widget *content=new bill_list_widget(this);
            content->initWidget(listData);
            ui->list_scroll->setWidget(content);
        }
        else{

        }
    });
}
/*
 * @
   拉伸列表重绘
*/
void CorePageWindow::resizeEvent(QResizeEvent *event){
    QSize size=this->size();

    ui->content_core_frame->resize(size.width()-45,size.height()-40);
    QSize frame_size=ui->content_core_frame->size();
    ui->list_content->resize(frame_size.width(),frame_size.height()-220);
    ui->list_top->resize(frame_size.width(),180);
    ui->statusBar->resize(frame_size.width()+15,22);
    ui->list_scroll->resize(frame_size.width(),frame_size.height()-220);
    ui->statusBar->move(0,frame_size.height()-8);
}
/*
 * @
   组件重载样式
*/
void CorePageWindow::paintEvent(QPaintEvent* e)
{
    QStyleOption option;
    option.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &p, this);
}
/*
 * @
   设置状态栏位置
*/
void CorePageWindow::setStatusBar(QStatusBar *st){
    st->resize(this->width()-20,22);
    st->move(0,this->height()-18);
}

CorePageWindow::~CorePageWindow()
{
    delete ui;
}
