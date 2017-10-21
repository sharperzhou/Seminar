#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ScrollProc(HWND, UINT, WPARAM, LPARAM);

int iFocused;
WNDPROC OldProc[3];

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS wndcls;
	HWND hwnd;
	MSG msg;
	static const TCHAR szAppName[] = TEXT("Palette");

	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = WndProc;
	wndcls.lpszClassName = szAppName;
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wndcls)) {
		MessageBox(NULL, TEXT("This is not a Windows NT Application"),
			szAppName, MB_OK | MB_ICONERROR);
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
	static HWND staticBkgrd, staticClr[3], staticNum[3];
	static HWND vscrollClr[3];
	static TCHAR *szClrName[] = {TEXT("红"), TEXT("绿"), TEXT("蓝")};
	static HINSTANCE hInstance;
	static RECT rect;
	static int nWidth, nHeight, cyChar, i;
	static COLORREF clrColor[] = {RGB(255,0,0), RGB(0,255,0), RGB(0,0,255)};
	static HBRUSH hBrushStatic, hBrushVScroll[3];
	static int nColor[3];

	switch (uMsg)
	{
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
		cyChar = HIWORD(GetDialogBaseUnits());

		hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_WINDOW));

		//背景区域的ID为9
		staticBkgrd = CreateWindow(TEXT("static"), 0, WS_CHILD | WS_VISIBLE | SS_WHITERECT,
			0, 0, 0, 0, hwnd, (HMENU) 9, hInstance, 0);

		for (i = 0; i < 3; i++) {

			//滚动条的ID为0至2
			vscrollClr[i] = CreateWindow(TEXT("ScrollBar"), 0, WS_CHILD | WS_VISIBLE | WS_TABSTOP | SBS_VERT,
				0, 0, 0, 0, hwnd, (HMENU) i, hInstance, 0);
			SetScrollRange(vscrollClr[i], SB_CTL, 0, 255, FALSE);
			SetScrollPos(vscrollClr[i], SB_CTL, 0, FALSE);

			//颜色标签的ID为3至5
			staticClr[i] = CreateWindow(TEXT("static"), szClrName[i], WS_CHILD | WS_VISIBLE | SS_CENTER,
				0, 0, 0, 0, hwnd, (HMENU) (i + 3), hInstance, 0);
			
			//RGB数值的ID为6至8
			staticNum[i] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER,
				0, 0, 0, 0, hwnd, (HMENU) (i + 6), hInstance, 0);

			hBrushVScroll[i] = CreateSolidBrush(clrColor[i]);

			OldProc[i] = (WNDPROC) SetWindowLong(vscrollClr[i], GWL_WNDPROC, (LONG) ScrollProc);
		}

		break;

	case WM_SIZE:
		nWidth = LOWORD(lParam); nHeight = HIWORD(lParam);
		SetRect(&rect, nWidth / 2, 0, nWidth, nHeight);

		MoveWindow(staticBkgrd, 0, 0, rect.right / 2, rect.bottom, TRUE);

		for (i = 0; i < 3; i++) {
			MoveWindow(vscrollClr[i], rect.right / 14 * (2 * i + 1), cyChar * 3,
				rect.right / 14, rect.bottom - cyChar * 6, TRUE);

			MoveWindow(staticClr[i], rect.right / 14 * (2 * i + 1), cyChar,
				rect.right / 14, cyChar, TRUE);

			MoveWindow(staticNum[i], rect.right / 14 * (2 * i + 1), rect.bottom - cyChar * 2,
				rect.right / 14, cyChar, TRUE);
		}

		SetFocus(hwnd);
		
		break;

	case WM_SETFOCUS:
		SetFocus(vscrollClr[iFocused]);
		break;

	case WM_VSCROLL:
		i = GetWindowLong((HWND) lParam, GWL_ID);
		switch (LOWORD(wParam))
		{
		case SB_LINEDOWN: nColor[i] += 1;   break;
		case SB_LINEUP:   nColor[i] -= 1;   break;
		case SB_PAGEDOWN: nColor[i] += 15;  break;
		case SB_PAGEUP:	  nColor[i] -= 15;  break;
		case SB_TOP:	  nColor[i]  = 0;   break;
		case SB_BOTTOM:   nColor[i]  = 255; break;

		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			nColor[i] = HIWORD(wParam); break;
		}
		nColor[i] = max(0, min(255, nColor[i]));
		SetScrollPos(vscrollClr[i], SB_CTL, nColor[i], TRUE);

		SetDlgItemInt(hwnd, i + 6, nColor[i], FALSE); 

		DeleteObject((HBRUSH)
			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)
				CreateSolidBrush(RGB(nColor[0], nColor[1], nColor[2]))));

		InvalidateRect(hwnd, &rect, TRUE);

		break;

	case WM_CTLCOLORSTATIC:
		i = GetWindowLong((HWND) lParam, GWL_ID);

		if (i >= 3 && i <= 8) {
			SetBkColor((HDC) wParam, GetSysColor(COLOR_WINDOW));
			SetTextColor((HDC) wParam, clrColor[i % 3]);
			return (LRESULT) hBrushStatic;
		}
		break;

	case WM_CTLCOLORSCROLLBAR:
		i = GetWindowLong((HWND) lParam, GWL_ID);

		if (i >= 0 && i <= 2)
			return (LRESULT) hBrushVScroll[i];

		break;

	case WM_SYSCOLORCHANGE:
		DeleteObject(hBrushStatic);
		hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
		break;

	case WM_DESTROY:

		//删除颜色文字创建的背景画刷
		DeleteObject((HGDIOBJ) hBrushStatic);
		
		//删除滚动条背景画刷
		for (i = 0; i < 3; i++)
			DeleteObject((HGDIOBJ) hBrushVScroll[i]);
		
		//删除窗口背景创建的画刷
		DeleteObject((HBRUSH)
			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)
				GetStockObject(WHITE_BRUSH)));

		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK ScrollProc(HWND hwndScroll, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int id = GetWindowLong(hwndScroll, GWL_ID);

	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (VK_TAB == wParam)
			SetFocus(GetNextDlgTabItem(GetParent(hwndScroll), hwndScroll, 
				GetKeyState(VK_SHIFT) < 0 ? TRUE : FALSE));
		break;
	case WM_SETFOCUS:
		iFocused = id;
		break;
	}

	return CallWindowProc(OldProc[id], hwndScroll, uMsg, wParam, lParam);
}