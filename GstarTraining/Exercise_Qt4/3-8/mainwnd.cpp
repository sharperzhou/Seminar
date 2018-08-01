#include "mainwnd.h"
#include <QTimer>
#include <QMutex>
#include "workerthread.h"

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
    , m_nRunFlag(0x00000001)
{
    ui.setupUi(this);
    m_mutex = new QMutex;
    for (int i = 0; i < 4; ++i) {
        m_threads[i] = new workerThread(this, m_mutex);
    }

    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    m_timer->setInterval(100);
    m_timer->start();

    connect(ui.btnRunOrSuspend, SIGNAL(clicked()),
        this, SLOT(onBtnRunOrSuspend()));
    connect(ui.btnReset, SIGNAL(clicked()),
        this, SLOT(onBtnReset()));
}

mainWnd::~mainWnd()
{
    m_timer->stop();
    delete m_timer;

    for (int i = 0; i < 4; ++i) {
        m_threads[i]->stop();
        m_threads[i]->wait();
        delete m_threads[i];
    }
    delete m_mutex;
}

void mainWnd::onTimer()
{
    QString str = QString::number(workerThread::number());
    ui.editAmount->setText(str);

    ui.lblState1->setText(status(m_threads[0]->status()));
    ui.lblState2->setText(status(m_threads[1]->status()));
    ui.lblState3->setText(status(m_threads[2]->status()));
    ui.lblState4->setText(status(m_threads[3]->status()));
}

QString mainWnd::status(workerThread::STATUS s) const
{
    const char* ret = NULL;
    switch (s) {
        case workerThread::STOPPED:  ret = "停止";  break;
        case workerThread::WAITTING: ret = "等待";  break;
        case workerThread::RUNNING:  ret = "运行";  break;
        default: break;
    }
    return QString::fromAscii(ret);
}

void mainWnd::onBtnRunOrSuspend()
{
    if (m_nRunFlag & (0x00000001 | 0x00000004)) {
        for (int i = 0; i < 4; ++i)
            m_threads[i]->start();
        ui.btnRunOrSuspend->setText(QString("暂停"));
        m_nRunFlag &= 0;
        m_nRunFlag |= 0x000000002;
        return;
    }

    if (m_nRunFlag & 0x000000002) {
        for (int i = 0; i < 4; ++i)
            m_threads[i]->stop();
        ui.btnRunOrSuspend->setText(QString("继续"));
        m_nRunFlag &= 0;
        m_nRunFlag |= 0x00000004;
        return;
    }
}

void mainWnd::onBtnReset()
{
    for (int i = 0; i < 4; ++i)
        m_threads[i]->reset();

    ui.btnRunOrSuspend->setText(QString("开始"));
    m_nRunFlag &= 0;
    m_nRunFlag |= 0x00000001;
}