#include "mainwnd.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());        //支持Tr中文
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale()); //支持中文文件名显示

    mainWnd w;
    w.show();
    return a.exec();
}
