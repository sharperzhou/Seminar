#include "mainwnd.h"
#include <QTimer>

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);
    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    m_timer->start();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
}

mainWnd::~mainWnd()
{
    m_timer->stop();
    delete m_timer;
}

void mainWnd::onTimer()
{
    int currentValue = ui.progressBar->value();
    ui.progressBar->setValue(++currentValue % 100);
}
