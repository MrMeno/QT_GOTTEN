#ifndef PUBLIC_MENU_HEADER_H
#define PUBLIC_MENU_HEADER_H

#include <QWidget>

namespace Ui {
class public_menu_header;
}

class public_menu_header : public QWidget
{
    Q_OBJECT

public:
    explicit public_menu_header(QWidget *parent = nullptr);
    ~public_menu_header();

private:
    Ui::public_menu_header *ui;
};

#endif // PUBLIC_MENU_HEADER_H
