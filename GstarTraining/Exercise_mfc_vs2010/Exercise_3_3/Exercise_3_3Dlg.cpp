
// Exercise_3_3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_3_3.h"
#include "Exercise_3_3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_3_3Dlg 对话框




CExercise_3_3Dlg::CExercise_3_3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_3_3Dlg::IDD, pParent)
    , m_hBitmap(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CExercise_3_3Dlg::~CExercise_3_3Dlg()
{
    BOOL bRet = DeleteObject(m_hBitmap);
}

void CExercise_3_3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExercise_3_3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_LOAD_BTN, &CExercise_3_3Dlg::OnBnClickedLoadBtn)
    ON_BN_CLICKED(IDC_SAVE_BTN, &CExercise_3_3Dlg::OnBnClickedSaveBtn)
END_MESSAGE_MAP()


// CExercise_3_3Dlg 消息处理程序

BOOL CExercise_3_3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    CRect rcClient;
    GetClientRect(rcClient);
    m_cx = rcClient.right - 120, m_cy = rcClient.bottom - 30;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_3_3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

    CDC *pDC = GetDC();
    CDC menDC;
    menDC.CreateCompatibleDC(pDC);
    menDC.SelectObject((HGDIOBJ) m_hBitmap);
    pDC->StretchBlt(0, 0, m_cx, m_cy, &menDC, 0, 0, m_cxBmp, m_cyBmp, SRCCOPY);
    ReleaseDC(pDC);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExercise_3_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExercise_3_3Dlg::OnBnClickedLoadBtn()
{
    CFileDialog fileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        _T("位图文件(*.bmp)|*.bmp||"), this);
    if (IDOK == fileDialog.DoModal()) {

        if (m_hBitmap)
            DeleteObject(m_hBitmap); //重复加载时先释放之前的资源

        do {
            m_hBitmap = (HBITMAP) LoadImage(AfxGetInstanceHandle(), fileDialog.GetPathName(),
                IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);

            if (!m_hBitmap) {
                MessageBox(_T("该位图已损坏，无法进行显示！"));
                break;
            }

            BITMAP bmp;
            ::GetObject((HANDLE) m_hBitmap, sizeof(BITMAP), (LPVOID) &bmp);
            m_cxBmp = bmp.bmWidth, m_cyBmp = bmp.bmHeight;

        } while (FALSE);

        Invalidate();
    }
}


void CExercise_3_3Dlg::OnBnClickedSaveBtn()
{
    if (!m_hBitmap) {
        MessageBox(_T("当前无位图文件可保存！"));
        return;
    }

    CFileDialog fileDialog(FALSE, NULL, _T("位图.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        _T("位图文件(*.bmp)|*.bmp||"), this);

    if (IDOK == fileDialog.DoModal()) {
        SaveBitmapToFile(m_hBitmap, fileDialog.GetPathName());
    }
}


BOOL CExercise_3_3Dlg::SaveBitmapToFile(HBITMAP hBitmap, LPCTSTR lpszFileName)  
{  
    HDC     hDC;           
    //当前分辨率下每象素所占字节数            
    int     iBits;           
    //位图中每象素所占字节数            
    WORD     wBitCount;           
    //定义调色板大小，     位图中像素字节大小     ，位图文件大小     ，     写入文件字节数                
    DWORD     dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;               
    //位图属性结构                
    BITMAP     Bitmap;                   
    //位图文件头结构            
    BITMAPFILEHEADER     bmfHdr;                   
    //位图信息头结构                
    BITMAPINFOHEADER     bi;                   
    //指向位图信息头结构                    
    LPBITMAPINFOHEADER     lpbi;                   
    //定义文件，分配内存句柄，调色板句柄                
    HANDLE     fh,   hDib,   hPal,hOldPal=NULL;               

    //计算位图文件每个像素所占字节数                
    hDC  = CreateDC(_T("DISPLAY"),   NULL,   NULL,   NULL);           
    iBits  = GetDeviceCaps(hDC,   BITSPIXEL)     *     GetDeviceCaps(hDC,   PLANES);               
    DeleteDC(hDC);               
    if(iBits <=  1)                                                     
        wBitCount = 1;               
    else  if(iBits <=  4)                                 
        wBitCount  = 4;               
    else if(iBits <=  8)                                 
        wBitCount  = 8;               
    else                                                                                                                                 
        wBitCount  = 24;  

    GetObject(hBitmap,   sizeof(Bitmap),   (LPSTR)&Bitmap);           
    bi.biSize= sizeof(BITMAPINFOHEADER);           
    bi.biWidth = Bitmap.bmWidth;           
    bi.biHeight =  Bitmap.bmHeight;           
    bi.biPlanes =  1;           
    bi.biBitCount = wBitCount;           
    bi.biCompression= BI_RGB;           
    bi.biSizeImage=0;           
    bi.biXPelsPerMeter = 0;           
    bi.biYPelsPerMeter = 0;           
    bi.biClrImportant = 0;           
    bi.biClrUsed =  0;           

    dwBmBitsSize  = ((Bitmap.bmWidth *wBitCount+31) / 32)*4* Bitmap.bmHeight;           

    //为位图内容分配内存                
    hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));               
    lpbi  = (LPBITMAPINFOHEADER)GlobalLock(hDib);               
    *lpbi  = bi;               

    //     处理调色板                    
    hPal  = GetStockObject(DEFAULT_PALETTE);               
    if (hPal)               
    {               
        hDC  = ::GetDC(NULL);               
        hOldPal = ::SelectPalette(hDC,(HPALETTE)hPal, FALSE);               
        RealizePalette(hDC);               
    }           

    //     获取该调色板下新的像素值                
    GetDIBits(hDC,hBitmap, 0,(UINT)Bitmap.bmHeight,    
        (LPSTR)lpbi+ sizeof(BITMAPINFOHEADER)+dwPaletteSize,     
        (BITMAPINFO *)lpbi, DIB_RGB_COLORS);               

    //恢复调色板                    
    if (hOldPal)               
    {               
        ::SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);               
        RealizePalette(hDC);               
        ::ReleaseDC(NULL,   hDC);               
    }               

    //创建位图文件                    
    fh  = CreateFile(lpszFileName,   GENERIC_WRITE,0,   NULL,   CREATE_ALWAYS,             
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,   NULL);               

    if (fh     ==  INVALID_HANDLE_VALUE)         return     FALSE;               

    //     设置位图文件头                
    bmfHdr.bfType  = 0x4D42;     //     "BM"                
    dwDIBSize  = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;                   
    bmfHdr.bfSize  = dwDIBSize;               
    bmfHdr.bfReserved1  = 0;               
    bmfHdr.bfReserved2  = 0;               
    bmfHdr.bfOffBits  = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;               
    //     写入位图文件头                
    WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER),   &dwWritten,   NULL);               
    //     写入位图文件其余内容                
    WriteFile(fh,   (LPSTR)lpbi,   dwDIBSize,   &dwWritten,   NULL);               
    //清除                    
    GlobalUnlock(hDib);               
    GlobalFree(hDib);               
    CloseHandle(fh);               

    return     TRUE;           

}  