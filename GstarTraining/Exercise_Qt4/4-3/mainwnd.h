#ifndef MAINWND_H
#define MAINWND_H

#include <QtGui/QMainWindow>
#include "ui_mainwnd.h"

class mainWnd : public QMainWindow
{
    Q_OBJECT

public:
    mainWnd(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~mainWnd();

private:
    Ui::mainWndClass ui;

    virtual void mouseMoveEvent(QMouseEvent *);

private slots:
    void onPopupMsg();
};

#endif // MAINWND_H
