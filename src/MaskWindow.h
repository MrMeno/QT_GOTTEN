#ifndef MASKWINDOW_H
#define MASKWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDesktopWidget>
#include <QSize>


namespace Ui {
class MaskWindow;
}

class MaskWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MaskWindow(QWidget *parent = nullptr);

    ~MaskWindow();
public slots:
    void getData(int timeSecond,QSize size);
private:
    Ui::MaskWindow *ui;
    int timeSecond;
    QSize size;
protected:
    void mouseDoubleClickEvent(QMouseEvent*);
};

#endif // MASKWINDOW_H
