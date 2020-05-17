#include "bill_list_widget.h"
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
bill_list_widget::bill_list_widget(QWidget *parent) : QWidget(parent)
{
   this->setMinimumWidth(300);
    this->setMinimumHeight(500);
}
void bill_list_widget::initWidget(QList<QVariant>& list)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    foreach (auto str,list)
    {
       // QMap<QString,QVariant> map_item=str.toMap();
      //  QString billNO=map_item.value("billNo").toString();
        QPushButton *button = new QPushButton("billNO", this);
        button->setMinimumSize(button->size());
        layout->addWidget(button);
    }
    this->setLayout(layout);
}
