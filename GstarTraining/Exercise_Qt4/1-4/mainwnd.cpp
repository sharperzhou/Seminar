#include "mainwnd.h"

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);
    connect(ui.radioName, SIGNAL(clicked()),
        this, SLOT(radioSelectionChanged()));
    connect(ui.radioSex, SIGNAL(clicked()),
        this, SLOT(radioSelectionChanged()));
}

mainWnd::~mainWnd()
{

}

void mainWnd::radioSelectionChanged()
{
    ui.editName->setEnabled(sender() == ui.radioName);
    ui.cboSex->setEnabled(sender() == ui.radioSex);
}