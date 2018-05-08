#include "mainwnd.h"
#include <QFileDialog>
#include <QPixmap>
#include <QImage>

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);
    connect(ui.btnLoad, SIGNAL(clicked()), this, SLOT(onBtnLoadClicked()));
    connect(ui.btnSave, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
}

mainWnd::~mainWnd()
{

}

void mainWnd::onBtnLoadClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开图片",
        "", "图片文件(*.bmp;*.jpg;*.png)");
    if (fileName.isEmpty()) return;

    QImage image;
    if (!image.load(fileName))
        return;

    ui.lblPic->setPixmap(QPixmap::fromImage(
        image.scaled(ui.lblPic->size())));
}

void mainWnd::onBtnSaveClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片",
        "未命名", "bmp文件(*.bmp);;jpg文件(*.jpg);;png文件(*.png);;");

    if (fileName.isEmpty()) return;

    ui.lblPic->pixmap()->save(fileName);
}