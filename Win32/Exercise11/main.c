#include <Windows.h>
#include <tchar.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
void PaintWindow(HWND hwnd, int iColor, int iFigure);
void PaintPic(HWND hPic, int iColor, int iFigure);

BOOL CenterWindow(HWND hwndWindow);

typedef struct
{
	int iColor;
	int iFigure;
} DlgData, *pDlgData;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS wndcls;
	HWND hwnd;
	MSG msg;
	const TCHAR szAppName[] = TEXT("PopupModelDlg");
	
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = WndProc;
	wndcls.lpszClassName = szAppName;
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	
	if (!RegisterClass(&wndcls)) {
		MessageBox(NULL, TEXT("This is not a Windows NT Application"), szAppName, MB_OK | MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, 0);

	ShowWindow(hwnd, nShowCmd);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu;
	static HINSTANCE hInstance;
	static DlgData dlgData = {IDC_RD_RED, IDC_RD_RECTANGLE};
	PAINTSTRUCT ps;

	switch (uMsg)
	{
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
		hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU));
		SetMenu(hwnd, hMenu);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_SETTING:
			if (DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DLG_SETTING), hwnd, DlgProc, (LPARAM) &dlgData))
				SendMessage(hwnd, WM_PAINT, 0, 0);
				InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		break;

	case WM_PAINT:
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);

		PaintWindow(hwnd, dlgData.iColor, dlgData.iFigure);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DlgData dlgData;
	static pDlgData pdlgData;
	static HWND hPic;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		CenterWindow(hwndDlg);

		pdlgData = (pDlgData) lParam;
		dlgData = *pdlgData;
		CheckRadioButton(hwndDlg, IDC_RD_RED, IDC_RD_BLACK, dlgData.iColor);
		CheckRadioButton(hwndDlg, IDC_RD_RECTANGLE, IDC_RD_TRIANGLE, dlgData.iFigure);
		hPic = GetDlgItem(hwndDlg, IDC_PIC);
		SetFocus(GetDlgItem(hwndDlg, dlgData.iColor));
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			*pdlgData = dlgData;
			EndDialog(hwndDlg, TRUE);
			break;

		case IDCANCEL:
			EndDialog(hwndDlg, FALSE);
			break;

		case IDC_RD_RED:
		case IDC_RD_GREEN:
		case IDC_RD_BLUE:
		case IDC_RD_YELLOW:
		case IDC_RD_WHITE:
		case IDC_RD_BLACK:
			dlgData.iColor = LOWORD(wParam);
			CheckRadioButton(hwndDlg, IDC_RD_RED, IDC_RD_BLACK, LOWORD(wParam));
			PaintPic(hPic, dlgData.iColor, dlgData.iFigure);
			break;

		case IDC_RD_RECTANGLE:
		case IDC_RD_ELIPSE:
		case IDC_RD_TRIANGLE:
			dlgData.iFigure = LOWORD(wParam);
			CheckRadioButton(hwndDlg, IDC_RD_RECTANGLE, IDC_RD_TRIANGLE, LOWORD(wParam));
			PaintPic(hPic, dlgData.iColor, dlgData.iFigure);
			break;
		}
		break;

	case WM_PAINT:
		PaintPic(hPic, dlgData.iColor, dlgData.iFigure);
		return FALSE;

	default:
		return FALSE;
	}

	return TRUE;
}

void PaintWindow(HWND hwnd, int iColor, int iFigure)
{
	COLORREF clr[] = { RGB(255,   0,   0),
					   RGB(  0, 255,   0),
					   RGB(  0,   0, 255),
					   RGB(255, 255,   0),
					   RGB(255, 255, 255),
					   RGB(  0,   0,   0) };

	HDC hdc = GetDC(hwnd);
	
	RECT rect;
	HBRUSH hbr;

	GetClientRect(hwnd, &rect);

	hbr = CreateSolidBrush(clr[iColor - IDC_RD_RED]);
	hbr = (HBRUSH) SelectObject(hdc, (HGDIOBJ) hbr);

	switch (iFigure)
	{
	case IDC_RD_RECTANGLE:
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		break;
	case IDC_RD_ELIPSE:
		Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
		break;
	case IDC_RD_TRIANGLE:
		{
			POINT apt[] = {rect.right / 2, 0, 0, rect.bottom - 1, rect.right - 1, rect.bottom - 1};
			Polygon(hdc, apt, 3);
		}
		break;
	}

	DeleteObject(SelectObject(hdc, hbr));
	
	ReleaseDC(hwnd, hdc);
}

void PaintPic(HWND hPic, int iColor, int iFigure)
{
	InvalidateRect(hPic, NULL, TRUE);
	UpdateWindow(hPic);
	PaintWindow(hPic, iColor, iFigure);
}

BOOL CenterWindow(HWND hwndWindow)
{
     HWND hwndParent;
     RECT rectWindow, rectParent, rectWorkArea;
	 int nWidth, nHeight, nX, nY;
 
     // make the window relative to its parent
     if ((hwndParent = GetParent(hwndWindow)) != NULL)
     {
         GetWindowRect(hwndWindow, &rectWindow);
         GetWindowRect(hwndParent, &rectParent);
 
         nWidth = rectWindow.right - rectWindow.left;
         nHeight = rectWindow.bottom - rectWindow.top;
 
         nX = ((rectParent.right - rectParent.left) - nWidth) / 2 + rectParent.left;
         nY = ((rectParent.bottom - rectParent.top) - nHeight) / 2 + rectParent.top;
 
         SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID) &rectWorkArea, 0);

         // make sure that the dialog box never moves outside of the screen
         if (nX < rectWorkArea.left) nX = rectWorkArea.left;
         if (nY < rectWorkArea.top) nY = rectWorkArea.top;
         if (nX + nHeight > rectWorkArea.right) nX = rectWorkArea.right - nWidth;
         if (nY + nHeight > rectWorkArea.bottom) nY = rectWorkArea.bottom - nHeight;
 
         MoveWindow(hwndWindow, nX, nY, nWidth, nHeight, FALSE);
 
         return TRUE;
     }
 
     return FALSE;
}
