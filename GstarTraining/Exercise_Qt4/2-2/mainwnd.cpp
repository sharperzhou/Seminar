#include "mainwnd.h"

mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);

    speed = ui.sliderSpeed->value();

    setScrollbarStep();

    red = ui.scrollRed->value();
    green = ui.scrollGreen->value();
    blue = ui.scrollBlue->value();
    palette.setColor(QPalette::Background, QColor(red, green, blue));

    setLabelValue();
    ui.lblSpeed->setNum(speed);

    ui.lblPic->setAutoFillBackground(true);
    ui.lblPic->setPalette(palette);

    connect(ui.scrollRed, SIGNAL(valueChanged(int)), this, SLOT(onScrollValueChanged(int)));
    connect(ui.scrollGreen, SIGNAL(valueChanged(int)), this, SLOT(onScrollValueChanged(int)));
    connect(ui.scrollBlue, SIGNAL(valueChanged(int)), this, SLOT(onScrollValueChanged(int)));
    connect(ui.sliderSpeed, SIGNAL(valueChanged(int)), this, SLOT(onScrollValueChanged(int)));
}

mainWnd::~mainWnd()
{

}

void mainWnd::onScrollValueChanged(int value)
{
    if (sender() == ui.sliderSpeed) {
        speed = value;
        ui.lblSpeed->setNum(speed);
        setScrollbarStep();
        return;
    } else if (sender() == ui.scrollRed) {
        red = value;
    } else if (sender() == ui.scrollGreen) {
        green = value;
    } else if (sender() == ui.scrollBlue) {
        blue = value;
    }


    setLabelValue();

    palette.setColor(QPalette::Background, QColor(red, green, blue));
    ui.lblPic->setPalette(palette);
}

void mainWnd::setScrollbarStep()
{
    ui.scrollRed->setSingleStep(speed);
    ui.scrollRed->setPageStep(speed);
    ui.scrollGreen->setSingleStep(speed);
    ui.scrollGreen->setPageStep(speed);
    ui.scrollBlue->setSingleStep(speed);
    ui.scrollBlue->setPageStep(speed);
}

void mainWnd::setLabelValue()
{
    ui.lblRed->setNum(red);
    ui.lblGreen->setNum(green);
    ui.lblBlue->setNum(blue);
}