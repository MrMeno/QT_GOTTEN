#include "CorePageWindow.h"
#include "ui_CorePageWindow.h"
#include <QApplication>
#include <qfile.h>
#include <qgraphicseffect.h>
#include <QMessageBox>
#include <QJsonObject>
#include <qdebug.h>
#include "util/httpService.h"

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

           // ui->list_content_data->setViewMode(QListView::ListMode);
            foreach(auto item,listData)
            {
                QMap<QString,QVariant> map_item=item.toMap();
                QString billNO=map_item.value("billNo").toString();
                qDebug()<<billNO;
               // QListWidgetItem* ui_item=new QListWidgetItem();


              //  ui_item->setText(billNO);
               // ui->list_content_data->addItem(ui_item);
            }

        }
        else{

        }
    });
}
void CorePageWindow::resizeEvent(QResizeEvent *event){
    QSize size=this->size();

    ui->content_core_frame->resize(size.width()-18,size.height()-18);
    QSize frame_size=ui->content_core_frame->size();
    ui->list_content->resize(frame_size.width(),frame_size.height()-205);
    ui->list_top->resize(frame_size.width(),180);
}
void CorePageWindow::paintEvent(QPaintEvent* e)
{
    QStyleOption option;
    option.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &p, this);
}
CorePageWindow::~CorePageWindow()
{
    delete ui;
}
