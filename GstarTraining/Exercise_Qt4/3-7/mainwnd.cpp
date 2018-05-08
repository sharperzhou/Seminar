#include "mainwnd.h"
#include <QSettings>
#include <QMessageBox>

#define KEY "HKEY_LOCAL_MACHINE\\SOFTWARE\\Qt Exercise\\"

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);
    connect(ui.btnNew, SIGNAL(clicked()), this, SLOT(onBtnNewClicked()));
    connect(ui.btnDel, SIGNAL(clicked()), this, SLOT(onBtnDelClicked()));
}

mainWnd::~mainWnd()
{

}

void mainWnd::onBtnNewClicked()
{
    QSettings settings(KEY, QSettings::NativeFormat);
    settings.setValue("ExePath", qApp->applicationFilePath());

    QMessageBox::information(this, "Tips", "已新建");
}

void mainWnd::onBtnDelClicked()
{
    QSettings settings(KEY, QSettings::NativeFormat);
    settings.clear();

    QMessageBox::information(this, "Tips", "已删除");
}