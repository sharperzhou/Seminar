#ifndef QSETTINGDLG_H
#define QSETTINGDLG_H

#include <QDialog>
#include "ui_qsettingdlg.h"

class QSettingDlg : public QDialog
{
    Q_OBJECT
    friend class mainWnd;

public:
    QSettingDlg(QWidget *parent = 0);
    ~QSettingDlg();

    void resetInfo();

private:
    Ui::QSettingDlg ui;

private slots:
    void onBtnBoxClicked(QAbstractButton *button);
};

#endif // QSETTINGDLG_H
