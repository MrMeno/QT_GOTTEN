#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "components/close_label_btn.h"
#include <QKeyEvent>
#include <functional>
#include <QLineEdit>
#include "CorePageWindow.h"
#include "components/drag_win_widget.h"
#include "util/httpService.h"

namespace Ui {//所有窗体对象都放在ui命名空间内
class LoginWindow;//声明登录窗体类
}

class LoginWindow : public QMainWindow//窗体继承自qt的窗体对象
{
    Q_OBJECT
    //QMainWindow继承自Qwidget，Qwidget继承自QObject，Q_OBJECT来自于qt核心类库中的宏
    //宏：相当于全局条件，根据自身定义的返回结果来替换掉程序中调用它的那部分，主要目的是为了缩减运行时间（宏置换在预处理过程中，宏展开在编译过程中，提升了程序运行效率）
    //此处用于将窗体类中使用宏的地方在预处理时替换，节省运行时间
public:
     LoginWindow(QWidget *parent = nullptr);
    //C++中的explicit关键字只能用于修饰只有一个参数的类构造函数,
    //它的作用是表明该构造函数是显示的, 而非隐式的, 跟它相对应的另一个关键字是implicit,
    //意思是隐藏的,类构造函数默认情况下即声明为implicit(隐式).
    bool eventFilter(QObject *obj, QEvent *event);
    void httpLogin();
     //HttpUtil *https=new HttpUtil(this);
    ~LoginWindow();//析构函数,释放函数时执行
private:
      Ui::LoginWindow *ui;
      CorePageWindow *cp;
    //此处变量ui等于loginwindow分配的内存地址
    //1、A.B则A为对象或者结构体；
    //2、A->B则A为指针，->是成员提取，A->B是提取A中的成员B，A只能是指向类、结构、联合的指针；
    //3、::是作用域运算符，A::B表示作用域A中的名称B，A可以是名字空间、类、结构；
    //4、:一般用来表示继承；
signals:

public slots:
        void slot_login_keydown();
};



#endif // LOGINWINDOW_H
