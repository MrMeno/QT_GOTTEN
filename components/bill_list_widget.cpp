#include "bill_list_widget.h"
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QMap>
bill_list_widget::bill_list_widget(QWidget *parent) : QWidget(parent)
{

}
void bill_list_widget::initWidget(QList<QVariant>& list)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    foreach (auto str,list)
    {
        //数据解析
        QMap<QString,QVariant> map_item=str.toMap();
        QString billMedia=map_item.value("billMedia").toString();
        QString billNO=map_item.value("billNo").toString();
        QString billAmountLower=map_item.value("billAmountLower").toString();
        QString acceptName=map_item.value("acceptName").toString();
        QString dueDate=map_item.value("dueDate").toString();
        QString endorsor=map_item.value("endorsor").toString();
        QList<QVariant> exceptionList=map_item.value("exceptionList").toList();

        //声明动态组件
        QWidget *content = new QWidget(this);//item最外层div
        content->setObjectName("list_item");
        QGridLayout *grid=new QGridLayout(this);//item最外层div布局
        QLabel *billMedia_value=new QLabel();//票据类型
        billMedia_value->setObjectName("item_title");
        QLabel *billNo_value=new QLabel();//票号
        billNo_value->setObjectName("item_value");
        QLabel *amount_value=new QLabel();//票号
        amount_value->setObjectName("item_value");
        QLabel *acceptName_value=new QLabel();//承兑人
        acceptName_value->setObjectName("item_value");
        QLabel *due_value=new QLabel();//到期日
        due_value->setObjectName("item_value");
        QLabel *endorsor_value=new QLabel();//背书人
        endorsor_value->setObjectName("item_value");
        QLabel *billNo_key=new QLabel();//票号
        billNo_key->setObjectName("item_key");
        QLabel *amount_key=new QLabel();//票号
        amount_key->setObjectName("item_key");
        QLabel *acceptName_key=new QLabel();//承兑人
        acceptName_key->setObjectName("item_key");
        QLabel *due_key=new QLabel();//到期日
        due_key->setObjectName("item_key");
        QLabel *endorsor_key=new QLabel();//背书人
        endorsor_key->setObjectName("item_key");
        QWidget *exWidget=new QWidget();//校验数据集
        QHBoxLayout *exLayout=new QHBoxLayout();//校验数据集
        foreach (auto ex_item, exceptionList) {
            QLabel *billListEx_item=new QLabel();//异常值
            billListEx_item->setObjectName("ex_label");
            billListEx_item->setMidLineWidth(85);
            billListEx_item->setMinimumHeight(20);
            billListEx_item->setAlignment(Qt::AlignCenter);
            QMap<QString,QVariant> ex_map=ex_item.toMap();
            QString exceDictValue=ex_map.value("exceDictValue").toString();
            billListEx_item->setStyleSheet("#ex_label"
                                           "{font-size:11px;"
                                           "background-color:'"+exBackWord(exceDictValue)+"'}");
            qDebug()<<exceDictValue;
            billListEx_item->setText(exceDictValue);
            exLayout->addWidget(billListEx_item);
        }
        exWidget->setLayout(exLayout);
        //数据填充
        billMedia_value->setText(billMedia);
        billNo_value->setText(billNO);
        amount_value->setText(billAmountLower);
        acceptName_value->setText(acceptName);
        due_value->setText(dueDate);
        endorsor_value->setText(endorsor);
        billNo_key->setText("票号");
        amount_key->setText("金额");
        acceptName_key->setText("承兑人");
        due_key->setText("到期日");
        endorsor_key->setText("背书人");
        //样式-》数据
        QString isBankType=(billMedia=="银票")?"#E59762":"#1991EB";
        grid->setRowMinimumHeight(8,30);
        //组件拼接
        grid->addWidget(billMedia_value,1,1,1,1,Qt::AlignLeft);

        grid->addWidget(billNo_key,3,1,1,1,Qt::AlignLeft);
        grid->addWidget(billNo_value,3,2,1,3,Qt::AlignLeft);

        grid->addWidget(amount_key,4,1,1,1,Qt::AlignLeft);
        grid->addWidget(amount_value,4,2,1,3,Qt::AlignLeft);

        grid->addWidget(acceptName_key,5,1,1,1,Qt::AlignLeft);
        grid->addWidget(acceptName_value,5,2,1,3,Qt::AlignLeft);

        grid->addWidget(due_key,6,1,1,1,Qt::AlignLeft);
        grid->addWidget(due_value,6,2,1,3,Qt::AlignLeft);

        grid->addWidget(endorsor_key,7,1,1,1,Qt::AlignLeft);
        grid->addWidget(endorsor_value,7,2,1,3,Qt::AlignLeft);

        grid->addWidget(exWidget,8,1,1,4,Qt::AlignLeft);
        //样式-》全局
        content->setStyleSheet("#list_item"
                               "{background-color:white;font-family:HanSans;max-height:300px}"
                               "#item_key"
                               "{color:'#C7C7C7';font-size:12px;}"
                               "#item_title"
                               "{font-size:15px;color:'"+isBankType+"';font-weight:bold}"
                                "#ex_label"
                               "{color:white;border-radius:2px;padding:0px 5px}");
        content->setLayout(grid);
        layout->addWidget(content,0,Qt::AlignTop);
    }
    this->setLayout(layout);
}
QString bill_list_widget::exBackWord(QString ex){
    QStringList T;
    T<<"黑名单银行"<<"黑名单企业"<<"敏感行业"
    <<"敏感行别"<<"上下不一致"<<"超期"<<"商票授信"
    <<"自有户"<<"非授信"<<"银票授信"<<"授信可收";
    if(T.contains(ex,Qt::CaseInsensitive)){
        return "#F7981C";
    }
    else{
        return "#F85359";
    };
}
