#include "stdafx.h"
#include "ExportMFCRegularDLL.h"
#include "func.h"
#include "MainDlg.h"

double AddData(double a, double b)
{
    return a + b;
}

double SubData(double a, double b)
{
    return a - b;
}

void ShowDlg()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CMainDlg dlg;
    dlg.DoModal();
}