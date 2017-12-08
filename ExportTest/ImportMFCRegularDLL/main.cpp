#include <Windows.h>
#include <tchar.h>
#include "..\ExportMFCRegularDLL\func.h"

int _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
    double ret;
    TCHAR str[1024] = {0};

    ret = AddData(1.2, 3.4);
    _stprintf(str, _T("1.2 + 3.4 = %f\n"), ret);
    ret = SubData(1.2, 3.4);
    _stprintf(str+_tcslen(str), _T("1.2 - 3.4 = %f"), ret);

    MessageBox(NULL, str, _T("²âÊÔ½á¹û"), MB_OK);
    ShowDlg();
    return 0;
}