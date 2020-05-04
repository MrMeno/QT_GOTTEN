#include "CorePageWindow.h"
#include "ui_CorePageWindow.h"

CorePageWindow::CorePageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CorePageWindow)
{
    ui->setupUi(this);
}

CorePageWindow::~CorePageWindow()
{
    delete ui;
}
