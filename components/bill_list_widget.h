#ifndef BILL_LIST_ITEM_H
#define BILL_LIST_ITEM_H
#include <QObject>
#include <QWidget>
#include <QMap>
class bill_list_widget:public QWidget
{
    Q_OBJECT
public:
   explicit  bill_list_widget(QWidget *parent = 0);
    void initWidget(QList<QVariant>& list);
};

#endif // BILL_LIST_ITEM_H
