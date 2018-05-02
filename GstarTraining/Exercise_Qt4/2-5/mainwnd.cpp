#include "mainwnd.h"
#include <QTreeWidgetItem>

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    connect(ui.treeInfo, SIGNAL(itemSelectionChanged()),
        this, SLOT(onItemSelChanged()));

    QTreeWidgetItem* item1 = ui.treeInfo->topLevelItem(0);

    QTreeWidgetItem* subItem1 = item1->child(0);
    QVariant data1 = QVariant::fromValue(subItem1->text(0) + "-ÄÐ-45");
    subItem1->setData(0, Qt::UserRole, data1);

    QTreeWidgetItem* subItem2 = item1->child(1);
    QVariant data2 = QVariant::fromValue(subItem2->text(0) + "-ÄÐ-23");
    subItem2->setData(0, Qt::UserRole, data2);

    QTreeWidgetItem* item2 = ui.treeInfo->topLevelItem(1);
    QTreeWidgetItem* subItem3 = item2->child(0);
    QVariant data3 = QVariant::fromValue(subItem3->text(0) + "-Å®-33");
    subItem3->setData(0, Qt::UserRole, data3);

    QTreeWidgetItem* subItem4 = item2->child(1);
    QVariant data4 = QVariant::fromValue(subItem4->text(0) + "-Å®-44");
    subItem4->setData(0, Qt::UserRole, data4);
}

mainWnd::~mainWnd()
{

}

void mainWnd::onItemSelChanged()
{
    QTreeWidgetItem* curItem = ui.treeInfo->currentItem();
    QString data = curItem->data(0, Qt::UserRole).toString();
    
    if (data == "") {
        ui.editName->setText("");
        ui.editSex->setText("");
        ui.editAge->setText("");
    } else {
        QStringList strList = data.split('-');
        ui.editName->setText(strList[0]);
        ui.editSex->setText(strList[1]);
        ui.editAge->setText(strList[2]);
    }
}