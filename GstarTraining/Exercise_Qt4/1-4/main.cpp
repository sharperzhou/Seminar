#include "mainwnd.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWnd w;
    w.show();
    return a.exec();
}
