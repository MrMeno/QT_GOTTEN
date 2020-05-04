#include <QLabel>
#include "close_label_btn.h"
#include <QApplication>
#include <windows.h>

Mylabel::Mylabel(QWidget *parent)
    :QLabel(parent)
{

     connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
}

void Mylabel::slotClicked()
{
   int nRet = QMessageBox::question(this, "消息", "确认退出？", tr("是"), tr("否"));
   if (0 == nRet) {
       QApplication::exit(0);
   }
    if (1 == nRet) {
    }

}
void Mylabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}
