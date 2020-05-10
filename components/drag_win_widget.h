#ifndef DRAG_WIN_WIDGET_H
#define DRAG_WIN_WIDGET_H
#include<QMainWindow>
#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>
class drag_win_widget:public QWidget
{
    Q_OBJECT
public:
    drag_win_widget(QWidget *parent=nullptr);
private:
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
    QWidget *father;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // DRAG_WIN_WIDGET_H
