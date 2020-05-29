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
#include <QMenu>
#include <QEvent>
#include <QDesktopServices>
#include <QUrl>


CorePageWindow::CorePageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CorePageWindow)
{
    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags()|Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowIcon(QIcon(":/img/logo.ico"));
    ui->setupUi(this);
    this->pageNo=1;
    this->pageSize=5;
    this->searchContent="";
    this->setStatusBar(ui->statusBar);
    setSystemTray();//设置系统托盘
    topInit();//初始化头部

    getListPage();//获取列表数据
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
    //控件声明初始化
    QLabel *imgLabel=new QLabel();//logo
    QLabel *titleLabel=new QLabel();//title
    titleLabel->setObjectName("titleLabel");
    QLabel *homeLabel=new QLabel();//home
    QLabel *setLabel=new QLabel();//设置
    QLabel *topLabel=new QLabel();//置顶
    topLabel->setObjectName("topLabel");
    QLabel *divLabel=new QLabel();//分隔
    divLabel->setObjectName("divLabel");
    QLabel *closeLabel=new QLabel();//关闭
    closeLabel->setObjectName("closeLabel");
    QLabel *minLabel=new QLabel();//最小化
    minLabel->setObjectName("minLabel");
    minLabel->setToolTip("最小化");
    QLabel *userNameLabel=new QLabel();//用户名
    userNameLabel->setToolTip("用户名");
    userNameLabel->setObjectName("userNameLabel");
    QLabel *orgLabel=new QLabel();//机构名称
    orgLabel->setObjectName("orgLabel");
    QLabel *orgDivLabel=new QLabel();//机构名称分隔
    QPushButton *ticketLftBtn=new QPushButton("添加票面",this);
     ticketLftBtn->setToolTip("添加票面");
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
    QLineEdit *searchBox=new QLineEdit();//搜索框
    searchBox->setToolTip("Enter键搜索");
    searchBox->setPlaceholderText("请输入票号查询");
    searchBox->setObjectName("searchContent");
    //事件绑定
    ticketLftBtn->installEventFilter(this);
    searchBox->installEventFilter(this);
    refresh->installEventFilter(this);
    closeLabel->installEventFilter(this);
    minLabel->installEventFilter(this);
    QObject::connect(searchBox,SIGNAL(returnPressed()),this,SLOT(searchBoxEnter()));

    //数据绑定
     QPixmap lo;
    if(lo.load(":/img/logo.ico")){
        imgLabel->setMaximumSize(20,20);
         imgLabel->setPixmap(lo.scaled(imgLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        imgLabel->setScaledContents(true);
    }
    QImage *lo_home=new QImage(16,16,QImage::Format_RGB32);
    if(lo_home->load(":/img/icon-home.png")){
        homeLabel->setMaximumSize(16,16);
        homeLabel->setPixmap(QPixmap::fromImage(*lo_home));
        homeLabel->setToolTip(u8"客户端每日24：00将自动清除当天数据\r\n若需要票据信息可到管理后台查询");
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
    setLabel->setCursor(Qt::PointingHandCursor);
    topLabel->setCursor(Qt::PointingHandCursor);
    closeLabel->setCursor(Qt::PointingHandCursor);
     homeLabel->setCursor(Qt::PointingHandCursor);
    ticketLftBtn->setCursor(Qt::PointingHandCursor);
    //控件排版
    topLayout->setVerticalSpacing(10);
    topLayout->setHorizontalSpacing(0);
    topLayout->addWidget(imgLabel,1,1,1,1,Qt::AlignLeft);//row1
    topLayout->addWidget(titleLabel,1,2,1,2,Qt::AlignLeft);
    topLayout->addWidget(homeLabel,1,7,1,2,Qt::AlignCenter);
    topLayout->addWidget(setLabel,1,8,1,2,Qt::AlignCenter);
    topLayout->addWidget(topLabel,1,9,1,2,Qt::AlignCenter);
    topLayout->addWidget(divLabel,1,10,1,2,Qt::AlignCenter);
    topLayout->addWidget(minLabel,1,11,1,2,Qt::AlignCenter);
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
    //填充控件
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
    if (obj->objectName()=="refresh")//刷新事件
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
    if(obj->objectName()=="searchContent"){//搜索框enter事件
        if (event->type() == QEvent::KeyRelease||event->type() == QEvent::FocusIn){
            //QInputMethod *inputEvent = dynamic_cast<QInputMethod*>(event);
            QLineEdit *s=qobject_cast<QLineEdit*>(obj);
            this->searchContent=s->text();
            qDebug()<<searchContent;
            return true;
        }
        else{
            return false;
        }
    }
    if(obj->objectName()=="ticketLftBtn"){//签票事件
        if (event->type() == QEvent::MouseButtonPress) //鼠标点击
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换
            if(mouseEvent->button() == Qt::LeftButton)
            {
                mask=new MaskWindow(this);
                mask->show();
                CorePageWindow::setVisibility(false);
            }
            return true;
        }
        else{
            return false;
        }
    }
    if(obj->objectName()=="closeLabel"){//关闭事件
        if (event->type() == QEvent::MouseButtonPress) //鼠标点击
        {
            QJsonObject *config=new QJsonObject();
            config->insert("contentText","确定退出？");
            config->insert("yesBtnText","退出");
            config->insert("noBtnText","不退出，最小化");
            config->insert("titleText","提示");
            dalog=new CustomerDialog(this,config,4);
            dalog->exec();
            qDebug()<<dalog->result();
            if(dalog->result()==1){
                appClose();
            }
            else if(dalog->result()==0){
                appMinimze();
            }
        }
        else{
            return false;
        }
    }
    if(obj->objectName()=="minLabel"){//最小化事件
        if (event->type() == QEvent::MouseButtonPress) //鼠标点击
        {
            appMinimze();
        }
        else{
            return false;
        }
    }
    if(obj->objectName()=="topLabel"){//置顶
        if (event->type() == QEvent::MouseButtonPress) //鼠标点击
        {
            this->setWindowFlags(Qt::WindowStaysOnTopHint);
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
void CorePageWindow::setVisibility(bool isShow){
    this->setVisible(isShow);
}
void CorePageWindow::setSystemTray(){
 trayIcon = new QSystemTrayIcon(this);
 trayIcon->setObjectName("systemTray");
 QIcon icon = QIcon(":/img/logo.ico");
 trayIcon->setIcon(icon);
 trayIcon->setToolTip("小ai签票");
 connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(on_activatedTrayIcon(QSystemTrayIcon::ActivationReason)));
 createActions();
 createMenu();
 trayIcon->show();


}

void CorePageWindow::on_activatedTrayIcon(QSystemTrayIcon::ActivationReason reason){
    switch(reason){
        case QSystemTrayIcon::Trigger:
            this->show();
            break;
        case QSystemTrayIcon::DoubleClick:
            this->show();
            break;

        default:
            break;
        }
}
void CorePageWindow::createActions()
{
    mShowMainAction = new QAction(QObject::trUtf8("显示主界面"),this);
    connect(mShowMainAction,SIGNAL(triggered()),this,SLOT(on_showMainAction()));

    mExitAppAction = new QAction(QObject::trUtf8("退出"),this);
    connect(mExitAppAction,SIGNAL(triggered()),this,SLOT(on_exitAppAction()));

}

void CorePageWindow::createMenu()
{
    mMenu = new QMenu(this);
    //新增菜单项---显示主界面
    mMenu->addAction(mShowMainAction);
    //增加分隔符
    mMenu->addSeparator();
    //新增菜单项---退出程序
    mMenu->addAction(mExitAppAction);
    //把QMenu赋给QSystemTrayIcon对象
    trayIcon->setContextMenu(mMenu);
}
void CorePageWindow::on_showMainAction()
{
    this->show();
}
void CorePageWindow::on_exitAppAction()
{
    exit(0);
}
void CorePageWindow::setStatusBar(QStatusBar *st){
    st->resize(this->width()-20,22);
    st->move(0,this->height()-18);
}
void CorePageWindow::appClose(){
    QApplication::quit();
}
void CorePageWindow::appMinimze(){
   this->hide();

}
void CorePageWindow::setTopWindow()
{
    Qt::WindowStates winStatus = Qt::WindowNoState;
    if (windowState() & Qt::WindowMaximized)
    {
        winStatus = Qt::WindowMaximized;
    }
    setWindowState(Qt::WindowActive | winStatus);
    activateWindow();
    raise();
}

CorePageWindow::~CorePageWindow()
{
    delete ui;
}
