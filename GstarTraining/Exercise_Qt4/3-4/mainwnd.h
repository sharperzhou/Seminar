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
    static bool compare(const QString& val1, const QString& val2);

private slots:
    void onBtnSortClicked();
};

#endif // MAINWND_H
