#ifndef COREPAGEWINDOW_H
#define COREPAGEWINDOW_H

#include <QMainWindow>

namespace Ui {
class CorePageWindow;
}

class CorePageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CorePageWindow(QWidget *parent = nullptr);
    ~CorePageWindow();

private:
    Ui::CorePageWindow *ui;
};

#endif // COREPAGEWINDOW_H
