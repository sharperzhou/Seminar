#ifndef MAINWND_H
#define MAINWND_H

#include <QtGui/QWidget>
#include "ui_mainwnd.h"

#include <QSystemTrayIcon>
#include <QMenu>

class mainWnd : public QWidget
{
    Q_OBJECT

public:
    mainWnd(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~mainWnd();

private:
    Ui::mainWndClass ui;
    QSystemTrayIcon* m_trayIcon;
    QMenu* m_contextMenu;
    QAction* m_showAction;
    QAction* m_quitAction;

private slots:
    void onBtnHideClicked();
    void showWnd(bool);
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAINWND_H
