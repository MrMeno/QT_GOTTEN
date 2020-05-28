#ifndef COREPAGEWINDOW_H
#define COREPAGEWINDOW_H
#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QObject>
#include "components/drag_win_widget.h"
#include "util/HttpUtil.h"
#include "util/httpService.h"
#include <QStatusBar>
#include <QScrollArea>
#include <QApplication>
#include "./src/MaskWindow.h"
#include "components/CustomerDialog.h"
namespace Ui {
class CorePageWindow;
}
class CorePageWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CorePageWindow(QWidget *parent = nullptr);
    void getListPage();
    void topInit();
    int pageSize;
    int pageNo;
    QString searchContent;
    void setVisibility(bool isShow);
    bool eventFilter(QObject *obj, QEvent *event);
    ~CorePageWindow();
private:
    Ui::CorePageWindow *ui;
    MaskWindow *mask;
    void appClose();
    void appMinimze();
    CustomerDialog *dalog;
public slots:
   void searchBoxEnter();
protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event);
    void setStatusBar(QStatusBar *st);
};

#endif // COREPAGEWINDOW_H
