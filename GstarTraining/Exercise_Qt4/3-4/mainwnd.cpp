#include "mainwnd.h"

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);
    connect(ui.btnSort, SIGNAL(clicked()), this, SLOT(onBtnSortClicked()));

}

mainWnd::~mainWnd()
{

}

void mainWnd::onBtnSortClicked()
{
    QString line = ui.editLine->text();
    if (line.isEmpty()) return;

    line = line.trimmed();
    QStringList strList = line.split(" ");
    if (strList.isEmpty()) return;

    qSort(strList.begin(), strList.end(), compare);

    QString newLine;
    for (int i = 0; i < strList.size(); ++i) {
        newLine.append(strList[i]);
        if (i < strList.size()-1) {
            newLine.append(' ');
        }
    }

    ui.editLine->setText(newLine);
}

bool mainWnd::compare(const QString& val1, const QString& val2)
{
    return val1.toInt() < val2.toInt();
}
