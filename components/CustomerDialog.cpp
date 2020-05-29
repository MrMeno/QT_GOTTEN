#include "CustomerDialog.h"
#include "ui_CustomerDialog.h"
#include <QDebug>
#include <qgraphicseffect.h>
#include "util/publicHelper.h"
#include <QGridLayout>
#include <QJsonObject>
#include <QPushButton>
CustomerDialog::CustomerDialog(QWidget *parent,QJsonObject *config,int type) :
    QDialog(parent),
    ui(new Ui::CustomerDialog)
{
    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags()|Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(10);	//设置圆角半径 像素
    shadowEffect->setColor(Qt::black);	// 设置边框颜色
    shadowEffect->setOffset(0);
    ui->title=new drag_win_widget(parent);
    ui->setupUi(this);
    ui->content_frame->setGraphicsEffect(shadowEffect);
    QPixmap bgImage(":/img/logo.ico");
    ui->title_logo->setPixmap(bgImage.scaled(ui->title_logo->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
      uiFormat(type,**&config);
    ui->icon_close->installEventFilter(this);
    ui->icon_close->setCursor(Qt::PointingHandCursor);
}
void CustomerDialog::uiFormat(int type,QJsonObject config){
    PublicHelper *helper=new PublicHelper();
    QString title_= (helper->getJsonValue(config,"titleText")).toVariant().toString();
    ui->title_text->setText(title_);
    QString contentText_= (helper->getJsonValue(config,"contentText")).toVariant().toString();
    QString yesBtnText_= (helper->getJsonValue(config,"yesBtnText")).toVariant().toString();
    QString noBtnText_= (helper->getJsonValue(config,"noBtnText")).toVariant().toString();
    QGridLayout *contentLayout=new QGridLayout();
    QGridLayout *footerLayout=new QGridLayout();
    QPushButton *yesBtn=new QPushButton();
    yesBtn->setObjectName("yesBtn");
    QPushButton *noBtn=new QPushButton();
    noBtn->setObjectName("noBtn");
    QLabel *conentLabel=new QLabel();
    conentLabel->setObjectName("conentLabel");
    ui->title_text->setText(title_);
    yesBtn->installEventFilter(this);
    noBtn->installEventFilter(this);
    switch(type){
    case 0:
        yesBtn->setText(yesBtnText_);
        conentLabel->setText(contentText_);
        contentLayout->addWidget(conentLabel,1,1,Qt::AlignCenter);
        footerLayout->addWidget(yesBtn,1,1,Qt::AlignCenter);
        ui->dialog_content->setLayout(contentLayout);
        ui->dialog_footer->setLayout(footerLayout);
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        yesBtn->setText(yesBtnText_);
        noBtn->setText(noBtnText_);
        conentLabel->setText(contentText_);
        contentLayout->addWidget(conentLabel,1,1,Qt::AlignCenter);
        footerLayout->addWidget(yesBtn,1,1,Qt::AlignCenter);
        footerLayout->addWidget(noBtn,1,2,Qt::AlignCenter);
        ui->dialog_content->setLayout(contentLayout);
        ui->dialog_footer->setLayout(footerLayout);
        break;
    case 5:
        break;
    default:
        break;
    }
}

bool CustomerDialog::eventFilter(QObject *obj, QEvent *event){
    if (obj->objectName()=="yesBtn")//是
    {
        if (event->type() == QEvent::MouseButtonRelease) //鼠标点击
        {
             this->accept();
             return true;
        }
        else{
            return false;
        }
    }
    if (obj->objectName()=="noBtn")//否
    {
        if (event->type() == QEvent::MouseButtonRelease) //鼠标点击
        {
              this->reject();
             return true;
        }
        else{
            return false;
        }
    }
    if (obj==ui->icon_close)//关闭弹窗
    {
        if (event->type() == QEvent::MouseButtonRelease) //鼠标点击
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换
            if(mouseEvent->button() == Qt::LeftButton)
            {
                this->reject();
                this->setResult(3);
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
    return true;
}
void CustomerDialog::paintEvent(QPaintEvent* e)
{
    QStyleOption option;
    option.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &p, this);
}

CustomerDialog::~CustomerDialog()
{
    delete ui;
}
