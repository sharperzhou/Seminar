#include "mainwnd.h"
#include <QLineEdit>

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);
    connect(ui.editVal1, SIGNAL(textChanged(const QString&)),
        this, SLOT(edit1Changed(const QString&)));
    connect(ui.editVal2, SIGNAL(textChanged(const QString&)),
        this, SLOT(edit2Changed(const QString&)));
}

mainWnd::~mainWnd()
{

}

void mainWnd::edit1Changed(const QString&)
{
    if (!ui.editVal1->hasFocus()) return;

    ui.editVal2->setText(ui.editVal1->text());
}

void mainWnd::edit2Changed(const QString&)
{
    if (!ui.editVal2->hasFocus()) return;

    ui.editVal1->setText(ui.editVal2->text());
}