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
#include <QRegExp>
#include <QValidator>
#include <util/publicHelper.h>
#include <QTime>
#include "util/DataBase.h"

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
    ui->title=new drag_win_widget(parent);
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

void LoginWindow::httpLogin(){
    QString userName=ui->userName->text();
    QString userPSW=ui->userPsw->text();
    QJsonObject *LoginDTO =new QJsonObject();
    LoginDTO->insert("userNo",userName.trimmed());
    LoginDTO->insert("userPass",userPSW.trimmed());
    httpService *serve=new httpService();
    serve->login(LoginDTO,[=](QJsonObject res){
        QString code=PublicHelper::getJsonValue(res,"code");
        QString token=PublicHelper::getJsonValue(res,"TICKETSESSIONSID");
        if(code==CODE_SUCCESS){
            loginAccount=userName;
            /*记录此次登录后，java返回的token*/
            QString current_date_time =QDateTime::currentDateTime().toString();
            DataBase *db=new DataBase();
            db->createConnection();
            QSqlQuery sql(db->d_b);
            //查询用户是否登录过
            sql.prepare(QString("select * from aibill_user "
                                "where account=%1").arg(userName));
            //登录过则更新上次的token
            if(sql.exec()){
                //qDebug()<<"user "+userName+" exist";
                sql.prepare(QString("update aibill_user set session_token=?,create_time=?,isCurrent=?"
                                    " where account=?"));
                sql.bindValue(0,token);
                sql.bindValue(1,current_date_time);
                sql.bindValue(2,1);
                sql.bindValue(3,userName.trimmed());
                sql.exec();
                if(!sql.exec()){
                    // QSqlError error=sql.lastError();
                    // qDebug()<<"update error:"+error.driverText();
                }
                else{
                   //  qDebug()<<"update success";
                }

            }
            //未登录过则新增用户登录的记录
            else{
                qDebug()<<userName+":none";
                 db->insert(userName,token);
            }
            /*打开主窗体*/
            cp=new CorePageWindow(this);
            cp->show();
            this->setHidden(true);
        }else{


        };});
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
