#ifndef POPUPWND_H
#define POPUPWND_H

#include <QDialog>
#include "ui_popupwnd.h"

class popupWnd : public QDialog
{
    Q_OBJECT

public:
    popupWnd(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~popupWnd();

public:
    Ui::popupWnd ui;

private slots:
    void onBtnOk();
};

#endif // POPUPWND_H
