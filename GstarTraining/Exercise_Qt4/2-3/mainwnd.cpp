#include "mainwnd.h"
#include <QFontDialog>
#include <QColorDialog>

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);

    m_font = ui.lblFont->font();
    ui.lblFont->setText(m_font.family());

    m_color = ui.lblColor->palette().color(QPalette::WindowText);
    ui.lblColor->setPalette(QPalette(QPalette::Background, m_color));

    SetPreview(SET_ALL);

    connect(ui.btnSelFont, SIGNAL(clicked()), this, SLOT(onBtnFontClicked()));
    connect(ui.btnSelColor, SIGNAL(clicked()), this, SLOT(onBtnColorClicked()));
}

mainWnd::~mainWnd()
{

}

void mainWnd::SetPreview(Setting sets)
{
    if (sets & SET_FONT) {
        ui.lblPreview->setFont(m_font);
    }

    if (sets & SET_COLOR) {
        QPalette palette;
        palette.setColor(QPalette::WindowText, m_color);
        ui.lblPreview->setPalette(palette);
    }
}

void mainWnd::onBtnFontClicked()
{
    bool fOk = false;
    m_font = QFontDialog::getFont(&fOk, m_font);

    if (fOk) {
        ui.lblFont->setText(m_font.family());
        SetPreview(SET_FONT);
    }
}

void mainWnd::onBtnColorClicked()
{
    m_color = QColorDialog::getColor(m_color);

    if (m_color.isValid()) {
        ui.lblColor->setPalette(QPalette(QPalette::Background, m_color));
        SetPreview(SET_COLOR);
    }
}