#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QApplication>
#include <qfile.h>
#include <qgraphicseffect.h>
#include <QMessageBox>
#include <QObject>
#include <QJsonObject>
#include <iterator>
#include <qdebug.h>
#include "util/HttpUtil.h"
#include <QRegExp>
#include <QValidator>
#include <util/publicHelper.h>
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{

    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags()| Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(10);	//设置圆角半径 像素
    shadowEffect->setColor(Qt::black);	// 设置边框颜色
    shadowEffect->setOffset(0);
    ui->setupUi(this);

    ui->content_frame->setGraphicsEffect(shadowEffect);
    ui->userName->setPlaceholderText("请输入用户名");
    ui->userPsw->setPlaceholderText("请输入密码");
     QRegExp regxPW("^[\\S]*$");
     QValidator *pwvalidator = new QRegExpValidator(regxPW, this );
     ui->userPsw->setValidator(pwvalidator);
      ui->userPsw->setEchoMode(QLineEdit::Password);
     ui->loginBtn->installEventFilter(this);
     ui->icon_min->installEventFilter(this);
     QObject::connect(ui->userPsw,SIGNAL(returnPressed()),this,SLOT(slot_login_keydown()));
}
void LoginWindow::mousePressEvent(QMouseEvent *event){
    //当鼠标左键点击时.
       if (event->button() == Qt::LeftButton)
       {
           m_move = true;
           //记录鼠标的世界坐标.
           m_startPoint = event->globalPos();
           //记录窗体的世界坐标.
           m_windowPoint = this->frameGeometry().topLeft();
       }
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
        this->move(m_windowPoint + relativePos );
    }
}
void LoginWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}

void LoginWindow::httpLogin(){
    QString userName=ui->userName->text();
    QString userPSW=ui->userPsw->text();
    QJsonObject *LoginDTO =new QJsonObject();
    LoginDTO->insert("userNo",userName.trimmed());
    LoginDTO->insert("userPass",userPSW.trimmed());
    HttpUtil *http=new HttpUtil();
    http->put(QUrl("/login"), LoginDTO,[=](QJsonObject res){
        qDebug() << "login-code:" << "success";
         QString code=PublicHelper::getJsonValue(res,"code");
         if(code==CODE_SUCCESS){
             cp=new CorePageWindow(this);
             cp->show();
             this->hide();
         }
    });
}
bool LoginWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->loginBtn)//指定某个QLabel
     {
         if (event->type() == QEvent::MouseButtonPress) //鼠标点击
         {
             QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换
             if(mouseEvent->button() == Qt::LeftButton)
             {
                 httpLogin();
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
    if (obj == ui->icon_min)//指定某个QLabel
     {
         if (event->type() == QEvent::MouseButtonPress) //鼠标点击
         {
             QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换
             if(mouseEvent->button() == Qt::LeftButton)
             {
                 this->showMinimized();
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
     return false;
}

 void LoginWindow::slot_login_keydown(){
    httpLogin();
}

 LoginWindow::~LoginWindow()
{
    delete ui;
}
