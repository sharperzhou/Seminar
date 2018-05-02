#include "qsettingdlg.h"
#include <QToolTip>

QSettingDlg::QSettingDlg(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.buttonBox, SIGNAL(clicked(QAbstractButton*)),
        this, SLOT(onBtnBoxClicked(QAbstractButton*)));

}

QSettingDlg::~QSettingDlg()
{

}

void QSettingDlg::onBtnBoxClicked(QAbstractButton *button)
{
    if (ui.buttonBox->button(QDialogButtonBox::Ok) == (QPushButton*) button) {
        if (ui.editName->text().trimmed().isEmpty()) {
            ui.editName->setFocus();
            QToolTip::showText(ui.editName->mapToGlobal(QPoint(0, 0)),
                ui.editName->toolTip());
        } else {
            accept();
        }
    } else if (ui.buttonBox->button(QDialogButtonBox::Cancel) == (QPushButton*) button) {
        reject();
    }
}

void QSettingDlg::resetInfo()
{
    ui.editName->setText("");
    ui.cboSex->setCurrentIndex(0);
    ui.spinAge->setValue(0);
}
