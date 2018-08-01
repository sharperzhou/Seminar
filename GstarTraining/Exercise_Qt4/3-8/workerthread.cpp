#include "workerthread.h"
#include <QMutexLocker>

workerThread::workerThread(QObject *parent, QMutex* mutex)
    : QThread(parent)
    , m_mutex(mutex)
    , m_bStopped(false)
    , m_status(STOPPED)
{
}

workerThread::~workerThread()
{

}

long workerThread::m_number = 0;

void workerThread::stop()
{
    m_bStopped = true;
}

void workerThread::reset()
{
    if (!m_bStopped)
        stop();
    m_number = 0;
}

void workerThread::run()
{
    while (!m_bStopped) {
        m_status = WAITTING;
        QMutexLocker locker(m_mutex);
        m_status = RUNNING;
        ++m_number;
        sleep(3);
    }
    m_status = STOPPED;
    m_bStopped = false;
}