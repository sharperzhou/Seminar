#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

class QMutex;
class workerThread : public QThread
{
    Q_OBJECT

public:
    enum STATUS {
        STOPPED,
        WAITTING,
        RUNNING,
    };

    explicit workerThread(QObject *parent, QMutex* mutex);
    ~workerThread();
    void stop();
    void reset();
    static long number() { return m_number; }
    STATUS status() const { return m_status; }

protected:
    virtual void run();

private:
    volatile bool m_bStopped;
    QMutex* m_mutex;
    static long m_number;
    STATUS m_status;
};

#endif // WORKERTHREAD_H
