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
#include <QLabel>
#include <QImage>
#include <QPushButton>
#include <QLineEdit>
#include <QMovie>
#include <QKeyEvent>


CorePageWindow::CorePageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CorePageWindow)
{
    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags()|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
    this->pageNo=1;
    this->pageSize=5;
    this->searchContent="";
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
    //控件声明
    QLabel *imgLabel=new QLabel();//logo
    QLabel *titleLabel=new QLabel();//title
    titleLabel->setObjectName("titleLabel");
    QLabel *homeLabel=new QLabel();//home
    QLabel *setLabel=new QLabel();//设置
    QLabel *topLabel=new QLabel();//置顶
    QLabel *divLabel=new QLabel();//分隔
    divLabel->setObjectName("divLabel");
    QLabel *closeLabel=new QLabel();//关闭
    QLabel *minLabel=new QLabel();//最小化
    QLabel *userNameLabel=new QLabel();//用户名
     userNameLabel->setObjectName("userNameLabel");
    QLabel *orgLabel=new QLabel();//机构名称
     orgLabel->setObjectName("orgLabel");
    QLabel *orgDivLabel=new QLabel();//机构名称分隔
    QPushButton *ticketLftBtn=new QPushButton("添加票面",this);
    ticketLftBtn->setObjectName("ticketLftBtn");
    QIcon up(":/img/arrow-up.png");
    QIcon down(":/img/arrow-down.png");
    QIcon fresh(":/img/icon-refresh.png");
    QPushButton *ticketRightBtn=new QPushButton(down,"",this);//签票按钮
    ticketRightBtn->setObjectName("ticketRightBtn");
    QLabel *signKeyLabel=new QLabel();//签票户
    signKeyLabel->setObjectName("signKeyLabel");
    QLabel *signValueLabel=new QLabel();//签票户
    signValueLabel->setObjectName("signValueLabel");
    QLabel *signLLabel=new QLabel();//签票户
    signLLabel->setObjectName("signLLabel");
    QLabel *signEditLabel=new QLabel();//签票户编辑
    signEditLabel->setObjectName("signEditLabel");
    QPushButton *refresh=new QPushButton(fresh,"",this);//刷新按钮
    refresh->setObjectName("refresh");
    refresh->installEventFilter(this);
    QLineEdit *searchBox=new QLineEdit();//搜索框
    searchBox->setObjectName("searchContent");
    searchBox->installEventFilter(this);
    QObject::connect(searchBox,SIGNAL(returnPressed()),this,SLOT(searchBoxEnter()));
    //空间内容

    QImage *lo=new QImage(20,20,QImage::Format_RGB32);
    if(lo->load(":/img/logo.png")){
        imgLabel->setMaximumSize(48,48);
        imgLabel->setPixmap(QPixmap::fromImage(*lo));
        imgLabel->setScaledContents(true);
    }
    QImage *lo_home=new QImage(16,16,QImage::Format_RGB32);
    if(lo_home->load(":/img/icon-home.png")){
        homeLabel->setMaximumSize(16,16);
        homeLabel->setPixmap(QPixmap::fromImage(*lo_home));
        homeLabel->setScaledContents(true);
    }
    QImage *lo_set=new QImage(16,16,QImage::Format_RGB32);
    if(lo_set->load(":/img/icon-set.png")){
        setLabel->setMaximumSize(16,16);
        setLabel->setPixmap(QPixmap::fromImage(*lo_set));
        setLabel->setScaledContents(true);
    }
    QImage *lo_top=new QImage(16,16,QImage::Format_RGB32);
    if(lo_top->load(":/img/icon-top.png")){
        topLabel->setMaximumSize(16,16);
        topLabel->setPixmap(QPixmap::fromImage(*lo_top));
        topLabel->setScaledContents(true);
    }
    QImage *lo_close=new QImage(16,16,QImage::Format_RGB32);
    if(lo_close->load(":/img/icon_close.png")){
        closeLabel->setMaximumSize(16,16);
        closeLabel->setPixmap(QPixmap::fromImage(*lo_close));
        closeLabel->setScaledContents(true);
    }
    QImage *lo_min=new QImage(16,16,QImage::Format_RGB32);
    if(lo_min->load(":/img/icon_remove.png")){
        minLabel->setMaximumSize(16,16);
        minLabel->setPixmap(QPixmap::fromImage(*lo_min));
        minLabel->setScaledContents(true);
    }
    QImage *lo_switch=new QImage(10,10,QImage::Format_RGB32);
    if(lo_switch->load(":/img/switcher.png")){
        orgDivLabel->setMaximumSize(10,10);
        orgDivLabel->setPixmap(QPixmap::fromImage(*lo_switch));
        orgDivLabel->setScaledContents(true);
    }
    titleLabel->setText("小ai签票");
    divLabel->setText("|");
    signKeyLabel->setText("签票户 ");
    signValueLabel->setText("2122121221");
    signLLabel->setText("杭州银行");
    signEditLabel->setText("编辑");
    QFontMetrics elideFont(orgLabel->font());
    orgLabel->setText(elideFont.elidedText(ORGNAME, Qt::ElideRight, ui->list_top->width()*0.42));
    userNameLabel->setText(USERNAME);

    //样式调整
    refresh->setCursor(Qt::PointingHandCursor);
    minLabel->setCursor(Qt::PointingHandCursor);
    closeLabel->setCursor(Qt::PointingHandCursor);
    ticketLftBtn->setCursor(Qt::PointingHandCursor);
   // searchBox->setStyleSheet("width:'"+QString::number((ui->list_top->width())*0.7)+"'px;");
    //植入控件
    topLayout->setVerticalSpacing(10);
    topLayout->setHorizontalSpacing(0);
    topLayout->addWidget(imgLabel,1,1,1,1,Qt::AlignRight);//row1
    topLayout->addWidget(titleLabel,1,2,1,2,Qt::AlignLeft);
    topLayout->addWidget(homeLabel,1,7,1,2,Qt::AlignCenter);
    topLayout->addWidget(setLabel,1,8,1,2,Qt::AlignCenter);
    topLayout->addWidget(topLabel,1,9,1,2,Qt::AlignCenter);
    topLayout->addWidget(divLabel,1,10,1,2,Qt::AlignCenter);
    topLayout->addWidget(minLabel,1,11,1,2,Qt::AlignRight);
    topLayout->addWidget(closeLabel,1,12,1,2,Qt::AlignRight);

    topLayout->addWidget(userNameLabel,3,1,1,3,Qt::AlignVCenter);//row2
    topLayout->addWidget(ticketLftBtn,3,8,2,3,Qt::AlignBottom|Qt::AlignRight);//row3+4
    topLayout->addWidget(ticketRightBtn,3,11,2,2,Qt::AlignBottom|Qt::AlignLeft);
    topLayout->addWidget(orgLabel,4,1,1,5,Qt::AlignLeft);//row4
    topLayout->addWidget(orgDivLabel,4,6,1,1,Qt::AlignLeft);
    topLayout->addWidget(signKeyLabel,5,1,1,1,Qt::AlignLeft);//row5
    topLayout->addWidget(signValueLabel,5,2,1,4,Qt::AlignLeft);
    topLayout->addWidget(signLLabel,5,6,1,3,Qt::AlignLeft);
    topLayout->addWidget(signEditLabel,5,11,1,3,Qt::AlignRight);
    topLayout->addWidget(refresh,6,1,2,2,Qt::AlignLeft);//row6+7
    topLayout->addWidget(searchBox,6,3,2,10,Qt::AlignLeft);
    ui->list_top->setLayout(topLayout);
}
/*
 * @
   获取列表数据
*/
void CorePageWindow::getListPage(){
    httpService *serve=new httpService();
    QJsonObject *param =new QJsonObject();
    //QMovie *movie = new QMovie(":/img/loading.gif");
    //ui->loading->setMovie(movie);
    //movie->start();
    param->insert("pageNo",QString::number(pageNo));
    param->insert("pageSize",QString::number(pageSize));
    param->insert("searchContent",searchContent);
    serve->getBillList(param,[=](QByteArray arr){
        QString str(arr);
        QScriptEngine engine;
        QScriptValue value=engine.evaluate("json="+str);
        QScriptValue code=value.property("code");
        if(code.toString()==CODE_SUCCESS){
            QScriptValue res_data=value.property("data");
            QScriptValue res_page=res_data.property("page");
            QScriptValue res_re=res_page.property("result");
            //qDebug()<<ui->scrollAreaWidgetContents;
            QList<QVariant> listData=  res_re.toVariant().toList();
            bill_list_widget *content=new bill_list_widget(this);
            content->initWidget(listData);
            ui->list_scroll->setWidget(content);
            //  movie->stop();
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
void CorePageWindow::searchBoxEnter(){

    getListPage();
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
bool CorePageWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj->objectName()=="refresh")//指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress) //鼠标点击
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换
            if(mouseEvent->button() == Qt::LeftButton)
            {
                pageNo=1;
                pageSize=5;
                searchContent="";
                getListPage();
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    if(obj->objectName()=="searchContent"){
        if (event->type() == QEvent::KeyRelease||event->type() == QEvent::FocusIn){
            //QInputMethod *inputEvent = dynamic_cast<QInputMethod*>(event);
            QLineEdit *s=qobject_cast<QLineEdit*>(obj);
            this->searchContent=s->text();
            qDebug()<<searchContent;
        }
        else{
            return false;
        }
    }

    return false;
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
