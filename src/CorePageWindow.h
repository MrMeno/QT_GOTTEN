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
#include <QSystemTrayIcon>
#include <components/system_tray.h>
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
    void setSystemTray();
    bool eventFilter(QObject *obj, QEvent *event);
    void createActions();
    void createMenu();
    void setTopWindow();
    ~CorePageWindow();
private:
    Ui::CorePageWindow *ui;
    MaskWindow *mask;
    void appClose();
    void appMinimze();
    QMenu *mMenu;
    QAction *mShowMainAction;
    QAction *mExitAppAction;
    CustomerDialog *dalog;
    QSystemTrayIcon *trayIcon;
public slots:
    void searchBoxEnter();
    void on_activatedTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void on_showMainAction();
    void on_exitAppAction();
protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event);
    void setStatusBar(QStatusBar *st);
};

#endif // COREPAGEWINDOW_H
