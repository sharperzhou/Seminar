#include "mainwnd.h"

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);
    connect(ui.fontComboBox, SIGNAL(currentFontChanged(const QFont&)),
        this, SLOT(onSelChanged(const QFont&)));
    QFont font;
    font.setFamily(QString::fromUtf8("ËÎÌו"));
    ui.fontComboBox->setCurrentFont(font);
}

mainWnd::~mainWnd()
{

}

void mainWnd::onSelChanged(const QFont& font)
{
    ui.lblFont->setText(font.family());
    ui.lblFont->setFont(font);
}
