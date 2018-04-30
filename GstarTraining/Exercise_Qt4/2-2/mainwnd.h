#ifndef MAINWND_H
#define MAINWND_H

#include <QtGui/QWidget>
#include "ui_mainwnd.h"

class mainWnd : public QWidget
{
    Q_OBJECT

public:
    mainWnd(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~mainWnd();

private:
    Ui::mainWndClass ui;
    int speed;
    int red;
    int green;
    int blue;
    QPalette palette;

    void setLabelValue();
    void setScrollbarStep();

private slots:
    void onScrollValueChanged(int);
};

#endif // MAINWND_H
