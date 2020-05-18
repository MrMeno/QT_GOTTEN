#ifndef COREPAGEWINDOW_H
#define COREPAGEWINDOW_H
#include <QMainWindow>
#include <QMouseEvent>
#include <QObject>
#include "components/drag_win_widget.h"
#include "util/HttpUtil.h"
#include "util/httpService.h"
#include <QStatusBar>
#include <QScrollArea>
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
    ~CorePageWindow();
private:
    Ui::CorePageWindow *ui;
protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event);
    void setStatusBar(QStatusBar *st);
};

#endif // COREPAGEWINDOW_H
