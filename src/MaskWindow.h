#ifndef MASKWINDOW_H
#define MASKWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDesktopWidget>
#include <QSize>
#include <QApplication>
namespace Ui {
class MaskWindow;
}

class MaskWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MaskWindow(QWidget *parent = nullptr);
    ~MaskWindow();

private:
    Ui::MaskWindow *ui;
};

#endif // MASKWINDOW_H
