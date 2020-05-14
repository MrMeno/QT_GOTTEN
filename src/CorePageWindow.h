#ifndef COREPAGEWINDOW_H
#define COREPAGEWINDOW_H
#include <QMainWindow>
#include <QMouseEvent>
#include <QObject>
#include "components/drag_win_widget.h"
#include "util/HttpUtil.h"
#include "util/httpService.h"
namespace Ui {
class CorePageWindow;
}
class CorePageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CorePageWindow(QWidget *parent = nullptr);
    void getListPage();
    ~CorePageWindow();

private:
    Ui::CorePageWindow *ui;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event);
};

#endif // COREPAGEWINDOW_H
