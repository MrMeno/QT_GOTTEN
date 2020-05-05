#include "public_menu_header.h"
#include "ui_public_menu_header.h"

public_menu_header::public_menu_header(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::public_menu_header)
{
    ui->setupUi(this);
}

public_menu_header::~public_menu_header()
{
    delete ui;
}
