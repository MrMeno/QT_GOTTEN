#include "bill_list_item.h"
#include "ui_bill_list_item.h"

bill_list_item::bill_list_item(QWidget *parent,QMap<QString,QVariant> *item) :
    QWidget(parent),
    ui(new Ui::bill_list_item)
{
    ui->setupUi(this);
}

bill_list_item::~bill_list_item()
{
    delete ui;
}
