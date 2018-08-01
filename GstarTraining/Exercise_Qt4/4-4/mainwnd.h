#ifndef MAINWND_H
#define MAINWND_H

#include <QtGui/QWidget>
#include "ui_mainwnd.h"

class StudentModel;
class AccessDBA;

class mainWnd : public QWidget
{
    Q_OBJECT

public:
    mainWnd(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~mainWnd();

private:
    Ui::mainWndClass ui;
    StudentModel* m_model;
    AccessDBA* m_database;

private slots:
    void onBtnAdd();
    void onBtnRemove();
    void onTableViewDoubleClicked(const QModelIndex& index);
};

#endif // MAINWND_H
