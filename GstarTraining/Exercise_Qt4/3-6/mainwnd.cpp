#include "mainwnd.h"


mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);
    connect(ui.btnHide, SIGNAL(clicked()),
        this, SLOT(onBtnHideClicked()));


    m_contextMenu = new QMenu(this);
    m_showAction = new QAction(QString::fromLocal8Bit("显示"), m_contextMenu);
    m_quitAction = new QAction(QString::fromLocal8Bit("退出"), m_contextMenu);
    m_contextMenu->addAction(m_showAction);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(m_quitAction);
    connect(m_showAction, SIGNAL(triggered(bool)),
        this, SLOT(showWnd(bool)));
    connect(m_quitAction, SIGNAL(triggered(bool)),
        qApp, SLOT(quit()));
    

    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setToolTip(QString::fromLocal8Bit("托盘提示"));
    m_trayIcon->setIcon(QIcon(":/mainWnd/Resources/trayicon.ico"));
    m_trayIcon->setContextMenu(m_contextMenu);
    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));
}

mainWnd::~mainWnd()
{
    showNormal();
    raise();
    activateWindow();
}

void mainWnd::onBtnHideClicked()
{
    
    if (!QSystemTrayIcon::isSystemTrayAvailable())
        return;

    m_trayIcon->show();
    if (QSystemTrayIcon::supportsMessages())
        m_trayIcon->showMessage(QString::fromLocal8Bit("托盘标题"),
        QString::fromLocal8Bit("托盘提示信息"));
    
    this->hide();
}

void mainWnd::showWnd(bool)
{
    showNormal();
    raise();
    activateWindow();
    m_trayIcon->hide();
}

void mainWnd::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
            showWnd(true);
            break;

        case QSystemTrayIcon::Context:
            m_contextMenu->show();
            break;

        default:
            break;
    }
}