// ImageViewer.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ImageViewer.h"
#include "ImageViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageViewerApp

BEGIN_MESSAGE_MAP(CImageViewerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CImageViewerApp 构造

CImageViewerApp::CImageViewerApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CImageViewerApp 对象

CImageViewerApp theApp;


// CImageViewerApp 初始化

BOOL CImageViewerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CImageViewerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此处放置处理何时用“确定”来关闭
		//  对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//  对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}


HBITMAP stretchImage(const HBITMAP hBmpSrc, int nWidth, int nHeight, bool bZoomIn/* = false*/)
{
    if (hBmpSrc == NULL) return NULL;

    BITMAP bmp;
    ::GetObject(hBmpSrc, sizeof(BITMAP), &bmp);
    int nWidthSrc = bmp.bmWidth, nHeightSrc = bmp.bmHeight;
    double dScale = min((double)nWidth/nWidthSrc, (double)nHeight/nHeightSrc);
    int nWidthDst = (dScale>1 && !bZoomIn) ? nWidthSrc : int(nWidthSrc*dScale);
    int nHeightDst = (dScale>1 && !bZoomIn) ? nHeightSrc : int(nHeightSrc*dScale);
    int nX = (nWidth - nWidthDst)/2;
    int nY = (nHeight - nHeightDst)/2;

    HDC hdc = ::GetDC(NULL);

    // source bitmap
    HDC hMenDCSrc = ::CreateCompatibleDC(hdc);
    HBITMAP hOldBmpSrc = (HBITMAP) ::SelectObject(hMenDCSrc, hBmpSrc);

    // destination bitmap
    HDC hMemDCDst = ::CreateCompatibleDC(hdc);
    HBITMAP hBmpDst = ::CreateCompatibleBitmap(hdc, nWidth, nHeight);
    HBITMAP hOldBmpDst = (HBITMAP) ::SelectObject(hMemDCDst, hBmpDst);

    ::SetStretchBltMode(hMemDCDst, HALFTONE);
    ::SetBrushOrgEx(hMemDCDst, 0, 0, NULL);
    ::StretchBlt(hMemDCDst, nX, nY, nWidthDst, nHeightDst,
        hMenDCSrc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

    ::SelectObject(hMemDCDst, hOldBmpDst);
    ::SelectObject(hMenDCSrc, hOldBmpSrc);
    ::ReleaseDC(NULL, hdc);
    ::DeleteDC(hMemDCDst);
    ::DeleteDC(hMenDCSrc);

    return hBmpDst;
}