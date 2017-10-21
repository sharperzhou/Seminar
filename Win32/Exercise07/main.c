#include <Windows.h>
#include <tchar.h>

#define TIMER1  1
#define TIMER2  2

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT iTimerID, DWORD dwTime);
void TextOutCurrentTime(LPTSTR timer_name, HDC hdc, int x, int y);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndcls;
	static const TCHAR szAppName[] = TEXT("TimerApp");

	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = WndProc;
	wndcls.lpszClassName = szAppName;
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_VREDRAW | CS_HREDRAW;

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
	PAINTSTRUCT ps;
	HDC hdc;

	switch (uMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, TIMER1, 1000, NULL);
		SetTimer(hwnd, TIMER2, 1000, TimerProc);
		break;

	case WM_TIMER:
		InvalidateRect(hwnd, NULL, FALSE);
		MessageBeep(-1);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOutCurrentTime(TEXT("Timer1"), hdc, 10, 10);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		KillTimer(hwnd, TIMER1);
		KillTimer(hwnd, TIMER2);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

void TextOutCurrentTime(LPTSTR timer_name, HDC hdc, int x, int y)
{
	SYSTEMTIME st;
	TCHAR szBuff[100] = {0};
	TEXTMETRIC tm;

	GetLocalTime(&st);
	
	GetTextMetrics(hdc, &tm);

	SetTextAlign(hdc, TA_TOP | TA_LEFT);
	TextOut(hdc, x, y, timer_name, lstrlen(timer_name));
	
	SetTextAlign(hdc, TA_TOP | TA_RIGHT);
	TextOut(hdc, x + 35 * tm.tmAveCharWidth, y, szBuff, wsprintf(szBuff, TEXT("%dƒÍ%d‘¬%d»’ %d:%02d:%02d"),
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond));
}

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT iTimerID, DWORD dwTime)
{
	HDC hdc = GetDC(hwnd);
	TextOutCurrentTime(TEXT("Timer2"), hdc, 10, 30);
	ReleaseDC(hwnd, hdc);
}