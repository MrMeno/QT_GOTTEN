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
 #include "util/DllHelper.h"
#include "util/ScreenUtil.h"
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
    ui->userName->setText("13556886172");
    ui->userPsw->setText("m123456");
    QObject::connect(ui->userPsw,SIGNAL(returnPressed()),this,SLOT(slot_login_keydown()));
}

void LoginWindow::httpLogin(){

    QString userName=ui->userName->text();
    QString userPSW=ui->userPsw->text();
    QJsonObject *LoginDTO =new QJsonObject();
    LoginDTO->insert("userNo",userName.trimmed());
    LoginDTO->insert("userPass",userPSW.trimmed());
    httpService *serve=new httpService();
    serve->login(LoginDTO,[=](QByteArray res){
        QString str(res);
        QScriptEngine engine;
        QScriptValue value=engine.evaluate("json="+str);
        QScriptValue code=value.property("code");
        QScriptValue data=value.property("data");
        QScriptValue userName=data.property("userName");
        QScriptValue orgName=data.property("orgName");
        USERNAME=userName.toString();
        ORGNAME=orgName.toString();
        if(code.toString()==CODE_SUCCESS){
            cp=new CorePageWindow(this);
            cp->show();
            this->setHidden(true);
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
