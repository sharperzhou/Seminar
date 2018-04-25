#include "mainwnd.h"



mainWnd::mainWnd(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    ui.setupUi(this);
    connect(ui.btnCalc, SIGNAL(clicked()), this, SLOT(onbtnCalc()));
    oper.insert("+", &mainWnd::Add);
    oper.insert("-", &mainWnd::Sub);
    oper.insert("*", &mainWnd::Mult);
    oper.insert("/", &mainWnd::Div);

    btnGroup = new QButtonGroup(this);
    btnGroup->addButton(ui.radioAdd);
    btnGroup->addButton(ui.radioSub);
    btnGroup->addButton(ui.radioMult);
    btnGroup->addButton(ui.radioDiv);
    btnGroup->setExclusive(true);
}

mainWnd::~mainWnd()
{
    delete btnGroup;
}

void mainWnd::onbtnCalc()
{
    PF pf = oper[btnGroup->checkedButton()->text()];
    double ret = 0;
    double val1 = ui.editVal1->text().toDouble();
    double val2 = ui.editVal2->text().toDouble();
    if ((*pf)(val1, val2, &ret)) {
        ui.editRes->setText(QString::number(ret));
    } else {
        ui.editRes->setText("N/A");
    }
}

bool mainWnd::Add(double a, double b, double* ret)
{
    *ret = a + b;
    return true;
}

bool mainWnd::Sub(double a, double b, double* ret)
{
    *ret = a - b;
    return true;
}

bool mainWnd::Mult(double a, double b, double* ret)
{
    *ret = a * b;
    return true;
}

bool mainWnd::Div(double a, double b, double* ret)
{
    if (b > -1e-15 && b < 1e-15) {
        return false;
    } else {
        *ret = a / b;
        return true;
    }
}