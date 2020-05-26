#ifndef MASKWINDOW_H
#define MASKWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDesktopWidget>
#include <QSize>
#include <QApplication>
#include "util/ScreenUtil.h"
namespace Ui {
class MaskWindow;
}

class MaskWindow : public QMainWindow
{
    Q_OBJECT

public:
      explicit MaskWindow(QWidget *parent = nullptr);
     void getDocument(HWND hwnd);
    ~MaskWindow();
public slots:
    void getData(int timeSecond,QSize size);

signals:
  // void mouseDoubleClickEvent(QMouseEvent *e);
private:
    Ui::MaskWindow *ui;
    int timeSecond;
    QSize size;
    QWidget *pIndow;
protected:
   virtual void mouseDoubleClickEvent(QMouseEvent *e)override;
};

#endif // MASKWINDOW_H
