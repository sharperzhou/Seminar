#include "popupwnd.h"

popupWnd::popupWnd(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    ui.setupUi(this);
    connect(ui.btnOk, SIGNAL(clicked()),
        this, SLOT(onBtnOk()));
}

popupWnd::~popupWnd()
{

}

void popupWnd::onBtnOk()
{
    accept();
}