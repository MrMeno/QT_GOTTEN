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
#include "components/bill_list_widget.h"

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
   // this->setWindowIcon(QIcon(":/img/logo.png"));
    ui->content_core_frame->setGraphicsEffect(shadowEffect);
    this->setStatusBar(ui->statusBar);
    getListPage();
}
void CorePageWindow::getListPage(){
    httpService *serve=new httpService();
    QJsonObject *param =new QJsonObject();
    param->insert("pageNo","1");
    param->insert("pageSize","10");
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
            /*  QList<QVariant>::iterator i;
            int counter=1;
            for(i=listData.begin();i!=listData.end();++i)
            {
                counter++;
                QMap<QString,QVariant> map_item=i->toMap();
                QString billNO=map_item.value("billNo").toString();
                qDebug()<<billNO;


            }*/
            bill_list_widget *content=new bill_list_widget(this);
            content->initWidget(listData);
            ui->list_scroll->setWidget(content);


        }
        else{

        }
    });
}
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
void CorePageWindow::paintEvent(QPaintEvent* e)
{
    QStyleOption option;
    option.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &p, this);
}
void CorePageWindow::setStatusBar(QStatusBar *st){
    st->resize(this->width()-20,22);
    st->move(0,this->height()-18);
}

CorePageWindow::~CorePageWindow()
{
    delete ui;
}
