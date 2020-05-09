#ifndef DRAG_WIN_WIDGET_H
#define DRAG_WIN_WIDGET_H
#include<QMainWindow>
#include <QWidget>
#include <QObject>
#include <QMouseEvent>
class drag_win_widget:public QWidget
{
    Q_OBJECT
public:
    drag_win_widget(QWidget *parent=nullptr,WId WinId=0);
private:
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
   unsigned int father;
   QWidget *f;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // DRAG_WIN_WIDGET_H
