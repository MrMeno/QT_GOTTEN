#include "drag_win_widget.h"
#include <QDebug>
#include <QObject>
drag_win_widget::drag_win_widget(QWidget *parent):QWidget(parent)
{
     father= parent;
}
void drag_win_widget::mousePressEvent(QMouseEvent *event){
    //当鼠标左键点击时.
       if (event->button() == Qt::LeftButton)
       {
           m_move = true;
           //记录鼠标的世界坐标.
           m_startPoint = event->globalPos();
           //记录窗体的世界坐标.
           m_windowPoint = this->father->parentWidget()->parentWidget()->frameGeometry().topLeft();
       }
}

void drag_win_widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;
        //然后移动窗体即可.
        this->father->parentWidget()->parentWidget()->move(m_windowPoint + relativePos );

    }
}
void drag_win_widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}

void drag_win_widget::paintEvent(QPaintEvent* e)
{
    QStyleOption option;
    option.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &p, this);
}
