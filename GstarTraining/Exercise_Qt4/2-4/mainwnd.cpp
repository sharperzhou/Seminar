#include "mainwnd.h"
#include "qsettingdlg.h"

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);

    connect(ui.btnSetting, SIGNAL(clicked()), this,
        SLOT(onBtnSettingClicked()));
}

mainWnd::~mainWnd()
{

}

void mainWnd::onBtnSettingClicked()
{
    QSettingDlg* settingDlg = new QSettingDlg(this);

    if (ui.editInfo->text().isEmpty()) {
        settingDlg->resetInfo();
    } else {
        QStringList strList = ui.editInfo->text().split('-');
        settingDlg->ui.editName->setText(strList.at(0));
        settingDlg->ui.cboSex->setEditText(strList.at(1));
        settingDlg->ui.spinAge->setValue(strList.at(2).toInt());
    }

    int ret = settingDlg->exec();

    if (QDialog::Accepted == ret) {
        ui.editInfo->setText(settingDlg->ui.editName->text() + "-"
            + settingDlg->ui.cboSex->currentText() + "-"
            + QString::number(settingDlg->ui.spinAge->value()));
    }
}