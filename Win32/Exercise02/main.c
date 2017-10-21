#include <Windows.h>
#include <tchar.h>
#include "SysMets.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawGrid(HDC hdc, int xOrg, int yOrg, int cxGrid, int cyGrid, int iBegRow, int iEndRow);
void DrawSysMets(HDC hdc, int xOrg, int yOrg, int *iColWidth, int cyText, int iBegRow, int iEndRow);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS wndcls;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("GridTextView");

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

	if (!RegisterClass(&wndcls))
	{
		MessageBox(NULL, TEXT("This is not a Windows NT Application"), szAppName,
			MB_OK | MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, 0);

	ShowWindow(hwnd, nShowCmd);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static TEXTMETRIC tm;
	static int cxChar, cyChar, cyGrid, cxClient, cyClient;
	static int iVertPos, iHorzPos;
	static int iColWidth[NUMCOL] = {0};
	static SCROLLINFO si = {0};

	switch (uMsg)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		cyGrid = cyChar + 6;
		ReleaseDC(hwnd, hdc);

		iColWidth[0] = cxChar * 38;
		iColWidth[1] = cxChar * 50;
		iColWidth[2] = cxChar * 5;

		si.cbSize = sizeof(SCROLLINFO);

		break;

	case WM_SIZE:
		cxClient = LOWORD(wParam); cyClient = HIWORD(wParam);

		
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = NUMROW - 1;
		si.nPage = cyClient / cyGrid;
		SetScrollInfo(hwnd, SBS_VERT, &si, TRUE);

		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = (iColWidth[0] + iColWidth[1] + iColWidth[2]) / cxChar;
		si.nPage = cxClient / cxChar;
		SetScrollInfo(hwnd, SBS_HORZ, &si, TRUE);

		break;

	case WM_VSCROLL:
		si.fMask = SIF_ALL;
		GetScrollInfo(hwnd, SBS_VERT, &si);
		iVertPos = si.nPos;

		switch (LOWORD(wParam))
		{
		case SB_LINEDOWN: si.nPos += 1; break;
		case SB_LINEUP:   si.nPos -= 1; break;
		case SB_TOP:      si.nPos = si.nMin; break;
		case SB_BOTTOM:   si.nPos = si.nMax; break;
		case SB_PAGEDOWN: si.nPos += si.nPage; break;
		case SB_PAGEUP:   si.nPos -= si.nPage; break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			si.nPos = HIWORD(wParam); break;
		}

		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SBS_VERT, &si, TRUE);
		GetScrollInfo(hwnd, SBS_VERT, &si);

		if (iVertPos != si.nPos) {
			ScrollWindow(hwnd, 0, cyChar * (iVertPos - si.nPos), NULL, NULL);
			//InvalidateRect(hwnd, NULL, TRUE);
			UpdateWindow(hwnd);
		}
		break;

	case WM_HSCROLL:
		si.fMask = SIF_ALL;
		GetScrollInfo(hwnd, SBS_HORZ, &si);
		iHorzPos = si.nPos;

		switch (LOWORD(wParam))
		{
		case SB_LINERIGHT:  si.nPos += 1; break;
		case SB_LINELEFT:   si.nPos -= 1; break;
		case SB_LEFT:       si.nPos = si.nMin; break;
		case SB_RIGHT:      si.nPos = si.nMax; break;
		case SB_PAGERIGHT:  si.nPos += si.nPage; break;
		case SB_PAGELEFT:   si.nPos -= si.nPage; break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			si.nPos = HIWORD(wParam); break;
		}

		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SBS_HORZ, &si, TRUE);
		GetScrollInfo(hwnd, SBS_HORZ, &si);

		if (iHorzPos != si.nPos) {
			ScrollWindow(hwnd, cxChar * (iHorzPos - si.nPos), 0, NULL, NULL);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		DrawGrid(hdc, 10, 10, iColWidth[0] - 3, cyGrid, 0, 8);
		DrawGrid(hdc, 10 + iColWidth[0] - 6, 10, iColWidth[1], cyGrid, 0, 8);
		DrawGrid(hdc, 10 + iColWidth[0] + iColWidth[1] - 9, 10,
			iColWidth[2] + 18, cyGrid, 0, 8);
		
		DrawSysMets(hdc, 13, 14, iColWidth, cyGrid, 0, 8);

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void DrawGrid(HDC hdc, int xOrg, int yOrg, int cxGrid, int cyGrid, int iBegRow, int iEndRow)
{
	int i;
	for (i = iBegRow; i <= iEndRow; i++) {
		MoveToEx(hdc, xOrg, yOrg + (i - iBegRow) * cyGrid, NULL);
		LineTo(hdc, xOrg + cxGrid, yOrg + (i - iBegRow) * cyGrid);
	}
	MoveToEx(hdc, xOrg + cxGrid, yOrg, NULL);
	LineTo(hdc, xOrg + cxGrid, yOrg + (iEndRow - iBegRow) * cyGrid);
}

void DrawSysMets(HDC hdc, int xOrg, int yOrg, int *iColWidth, int cyText, int iBegRow, int iEndRow)
{
	int i;
	TCHAR szBuff[10];

	for (i = iBegRow; i < iEndRow; i++) {
		SetTextAlign(hdc, TA_LEFT | TA_TOP);
		TextOut(hdc, xOrg, yOrg + (i - iBegRow) * cyText, sysmetrics[i].szLabel,
			lstrlen(sysmetrics[i].szLabel));
		TextOut(hdc, xOrg + iColWidth[0], yOrg + (i - iBegRow) * cyText, sysmetrics[i].szDesc, 
			lstrlen(sysmetrics[i].szDesc));

		SetTextAlign(hdc, TA_RIGHT | TA_TOP);
		TextOut(hdc, xOrg + iColWidth[0] + iColWidth[1] + iColWidth[2],
			yOrg + (i - iBegRow) * cyText, szBuff,
			wsprintf(szBuff, TEXT("%d"), sysmetrics[i].iIndex));
	}
}