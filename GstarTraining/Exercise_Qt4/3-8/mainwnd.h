#ifndef MAINWND_H
#define MAINWND_H

#include <QtGui/QWidget>
#include "ui_mainwnd.h"
#include "workerthread.h"

class QMutex;
class mainWnd : public QWidget
{
    Q_OBJECT

public:
    mainWnd(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~mainWnd();

private:
    Ui::mainWndClass ui;
    workerThread* m_threads[4];
    QTimer* m_timer;
    QMutex* m_mutex;
    char m_nRunFlag; // 0x00000001 start, 0x00000002 suspend, 0x00000004 resume
    QString status(workerThread::STATUS s) const;
    bool canRun() const;
    bool canSuspend() const;
    bool canReset() const;

private slots:
    void onTimer();
    void onBtnRunOrSuspend();
    void onBtnReset();
};

#endif // MAINWND_H
