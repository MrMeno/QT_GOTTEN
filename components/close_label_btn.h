#ifndef MYLABEL_H
#define MYLABEL_H
#include<QLabel>
#include<QString>
#include<QWidget>
#include<QMainWindow>
#include <QMessageBox>

class Mylabel:public QLabel
{
    Q_OBJECT
public:
    Mylabel(QWidget *parent=0);
    ~Mylabel(){}
signals:
    void clicked();
public slots:
    void slotClicked();
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // MYLABEL_H
