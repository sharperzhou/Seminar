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
    typedef bool (*PF)(double, double, double*);
    Ui::mainWndClass ui;
    QMap<QString, PF> oper;
    QButtonGroup* btnGroup;

    static bool Add(double a, double b, double* ret);
    static bool Sub(double a, double b, double* ret);
    static bool Mult(double a, double b, double* ret);
    static bool Div(double a, double b, double* ret);

private slots:
    void onbtnCalc();
};

#endif // MAINWND_H
