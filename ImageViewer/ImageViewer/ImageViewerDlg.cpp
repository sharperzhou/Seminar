// ImageViewerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <atlimage.h>
#include "ImageViewer.h"
#include "ImageViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageViewerDlg 对话框


bool stretchImage(const CImage& srcImg, CImage& dstImg, int nWidth, int nHeight);

BOOL GetImageThumb(HBITMAP hSrcBmp, int cx, int cy, COLORREF bkColor, HBITMAP *hDstBmp);

CImageViewerDlg::CImageViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageViewerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageViewerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_PREVIEW, m_listPreview);
    DDX_Control(pDX, IDC_STATIC_VIEW, m_staticView);
}

BEGIN_MESSAGE_MAP(CImageViewerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_COMMAND(ID_OPEN, &CImageViewerDlg::OnOpen)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PREVIEW, &CImageViewerDlg::OnLvnItemchangedListPreview)
END_MESSAGE_MAP()


// CImageViewerDlg 消息处理程序

BOOL CImageViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    CMenu menu;
    menu.LoadMenu(IDR_MENU);
    SetMenu(&menu);
    m_hAccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR));
    m_imageList.Create(96, 96, ILC_COLOR32 | ILC_MASK, 8, 4);
    m_listPreview.SetImageList(&m_imageList, LVSIL_NORMAL);
    DWORD dwExStyle = m_listPreview.GetExtendedStyle();
    dwExStyle |= LVS_EX_HIDELABELS;
    m_listPreview.SetExtendedStyle(dwExStyle);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImageViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CImageViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CImageViewerDlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
    if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
        if (m_hAccel != NULL && ::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
            return TRUE;

    return CDialog::PreTranslateMessage(pMsg);
}

void CImageViewerDlg::OnOpen()
{
    // TODO: 在此添加命令处理程序代码

    CFileDialog dlg(TRUE, NULL, NULL, 
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT | OFN_EXPLORER);
    const DWORD dwBufSize = 5*MAX_PATH;
    TCHAR* pBuf = new TCHAR[dwBufSize];
    ::ZeroMemory(pBuf, sizeof(TCHAR)*dwBufSize);
    dlg.m_ofn.lpstrFile = pBuf;
    dlg.m_ofn.nMaxFile = dwBufSize;

    if (IDOK == dlg.DoModal()) {
        m_listPreview.DeleteAllItems();
        m_imageList.Remove(-1);

        POSITION pos = dlg.GetStartPosition();
        while (pos != NULL) {
            CString strFileName = dlg.GetNextPathName(pos);
            CImage imgOrg, imgModify;
            HRESULT hr = imgOrg.Load(strFileName);
            if (SUCCEEDED(hr)) {
                HBITMAP hBmp;
                hBmp = stretchImage(imgOrg, 96, 96);
                ASSERT(hBmp);
                CBitmap bmp;
                bmp.Attach(hBmp);
                int index = m_imageList.Add(&bmp, RGB(0,0,0));
                m_listPreview.InsertItem(index, strFileName, index);
            }
        }

        m_listPreview.SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
        m_listPreview.SetSelectionMark(0);

    }
}

void CImageViewerDlg::OnLvnItemchangedListPreview(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码
    if ((pNMLV->uChanged & LVIF_STATE) && (pNMLV->uNewState & LVIS_SELECTED)) {
        int nItem = pNMLV->iItem;
        CString strImgPath = m_listPreview.GetItemText(nItem, 0);
        m_staticView.Load(strImgPath);
        m_staticView.Invalidate();
    }

    *pResult = 0;
}
