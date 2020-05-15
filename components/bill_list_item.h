#ifndef BILL_LIST_ITEM_H
#define BILL_LIST_ITEM_H

#include <QWidget>

namespace Ui {
class bill_list_item;
}

class bill_list_item : public QWidget
{
    Q_OBJECT

public:
    explicit bill_list_item(QWidget *parent = 0,QMap<QString,QVariant> *item=nullptr);
    ~bill_list_item();

private:
    QVariantMap *item;
    Ui::bill_list_item *ui;
};

#endif // BILL_LIST_ITEM_H
