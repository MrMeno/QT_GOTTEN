#include "bill_list_widget.h"
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
bill_list_widget::bill_list_widget(QWidget *parent) : QWidget(parent)
{

}
void bill_list_widget::initWidget(QList<QVariant>& list)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    foreach (auto str,list)
    {
        //声明动态组件
        QWidget *content = new QWidget(this);//item最外层div
        content->setObjectName("list_item");
        content->setStyleSheet("#list_item{background-color:white;}");
        QGridLayout *grid=new QGridLayout(this);//item最外层div布局
        QLabel *billNo_value=new QLabel();
        QLabel *amount_value=new QLabel();
        QLabel *acceptName_value=new QLabel();
        QLabel *due_value=new QLabel();
        QLabel *endorsor_value=new QLabel();
         //数据解析
         QMap<QString,QVariant> map_item=str.toMap();
         QString billNO=map_item.value("billNo").toString();
         QString billAmountLower=map_item.value("billAmountLower").toString();
         QString acceptName=map_item.value("acceptName").toString();
         QString dueDate=map_item.value("dueDate").toString();
         QString endorsor=map_item.value("endorsor").toString();
         //数据填充
         billNo_value->setText("票号 "+billNO);
         amount_value->setText("金额 " +billAmountLower);
         acceptName_value->setText("承兑人 " +acceptName);
         due_value->setText("到期日 " +billAmountLower);
         endorsor_value->setText("背书人 " +acceptName);
         //组件拼接
         grid->addWidget(billNo_value,1,1,Qt::AlignLeft);
         grid->addWidget(amount_value,2,1,Qt::AlignLeft);
         grid->addWidget(acceptName_value,3,1,Qt::AlignLeft);
         grid->addWidget(due_value,4,1,Qt::AlignLeft);
         grid->addWidget(endorsor_value,5,1,Qt::AlignLeft);
         content->setLayout(grid);
         content->setMinimumHeight(200);
         layout->addWidget(content);
    }
    this->setLayout(layout);
}
