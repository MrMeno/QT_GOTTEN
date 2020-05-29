#ifndef SYSTEM_TRAY_H
#define SYSTEM_TRAY_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QSystemTrayIcon>
#include <QWidgetAction>
#include <QPushButton>
#include <QLabel>
#include <QEvent>
#include <QPainter>
#include <QLayout>
#include <QMenu>
class system_tray:public QSystemTrayIcon
{
    Q_OBJECT
public:
    system_tray(QWidget *parent=nullptr);
    bool eventFilter(QObject *watched, QEvent *event);
    void createTopWidget();
    void createBottomWidget();
private:
    QMenu* m_trayMenu;

    QWidget* m_topWidget;
    QWidgetAction* m_topWidgetAction;
    QLabel* m_topLabel;
    QLabel* m_homeBtn;

    QWidget* m_bottomWidget;
    QWidgetAction* m_bottomWidgetAction;
    QPushButton* m_updateBtn;
    QPushButton* m_aboutBtn;
    QPushButton* m_exitBtn;

    QAction* m_runOnSystemBoot;
    QAction* m_helpOnline;
    QAction* m_homePage;
    QAction* m_notification;
    QAction* m_settings;
};

#endif // SYSTEM_TRAY_H
