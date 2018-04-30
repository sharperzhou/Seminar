#ifndef MAINWND_H
#define MAINWND_H

#include <QtGui/QWidget>
#include "ui_mainwnd.h"

class mainWnd : public QWidget
{
    Q_OBJECT
private:
    enum Setting {
        SET_FONT = 0x01,
        SET_COLOR = 0x10,
        SET_ALL = SET_FONT | SET_COLOR,
    };

public:
    mainWnd(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~mainWnd();

private:
    Ui::mainWndClass ui;
    QFont m_font;
    QColor m_color;
    void SetPreview(Setting sets);

private slots:
    void onBtnFontClicked();
    void onBtnColorClicked();
};

#endif // MAINWND_H
