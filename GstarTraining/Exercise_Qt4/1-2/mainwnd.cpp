#include "mainwnd.h"
#include <QListWidget>

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    connect(ui.listInfo, SIGNAL(itemSelectionChanged()),
        this, SLOT(listInfoSelectionChanged()));
    connect(ui.btnAddOne, SIGNAL(clicked()),
        this, SLOT(btnAddOneClicked()));
    connect(ui.listPrint, SIGNAL(itemSelectionChanged()),
        this, SLOT(listPrintSelectionChanged()));
    connect(ui.btnRemoveOne, SIGNAL(clicked()),
        this, SLOT(btnRemoveOneClicked()));
    connect(ui.btnAddAll, SIGNAL(clicked()),
        this, SLOT(btnAddAllClicked()));
    connect(ui.btnRemoveAll, SIGNAL(clicked()),
        this, SLOT(btnRemoveAllClicked()));

}

mainWnd::~mainWnd()
{

}

void mainWnd::listInfoSelectionChanged()
{
    ui.btnAddOne->setEnabled(ui.listInfo->selectedItems().count() > 0);
}

void mainWnd::btnAddOneClicked()
{
    QList<QListWidgetItem*>& selectItems = ui.listInfo->selectedItems();
    for (int i = 0; i < selectItems.count(); ++i) {
        QString strItemText = selectItems.at(i)->text();
        if (ui.listPrint->findItems(strItemText, Qt::MatchExactly).isEmpty()) {
            QListWidgetItem* newItem = new QListWidgetItem(strItemText);
            ui.listPrint->addItem(newItem);
        }
    }
}

void mainWnd::listPrintSelectionChanged()
{
    ui.btnRemoveOne->setEnabled(ui.listPrint->selectedItems().count() > 0);
}

void mainWnd::btnRemoveOneClicked()
{
    QList<QListWidgetItem*>& selectItems =  ui.listPrint->selectedItems();
    for (int i = selectItems.count() - 1; i >= 0; --i) {
        delete selectItems.at(i);
        selectItems.removeAt(i);
    }
}

void mainWnd::btnAddAllClicked()
{
    ui.listPrint->clear();
    for (int i = 0; i < ui.listInfo->count(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(ui.listInfo->item(i)->text());
        ui.listPrint->addItem(item);
    }
}

void mainWnd::btnRemoveAllClicked()
{
    ui.listPrint->clear();
}