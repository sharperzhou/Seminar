
// Exercise_5_1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Exercise_5_1.h"
#include "Exercise_5_1Dlg.h"
#include "afxdialogex.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExercise_5_1Dlg 对话框

#ifdef _UNICODE
#define CF_TCHARTEXT CF_UNICODETEXT
#else
#define CF_TCHARTEXT CF_TEXT
#endif



CExercise_5_1Dlg::CExercise_5_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExercise_5_1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExercise_5_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExercise_5_1Dlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_LOAD_BTN, &CExercise_5_1Dlg::OnBnClickedLoadBtn)
    ON_BN_CLICKED(IDC_SAVE_BTN, &CExercise_5_1Dlg::OnBnClickedSaveBtn)
    ON_COMMAND_RANGE(ID_FILE_LOAD1, ID_EDIT_SELECTALL1, &CExercise_5_1Dlg::OnPopupMenuClicked)
    ON_WM_INITMENUPOPUP()
    ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CExercise_5_1Dlg 消息处理程序

BOOL CExercise_5_1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    CMenu menu;
    menu.LoadMenu(IDR_MENU);
    SetMenu(&menu);
    
    m_hAccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR));

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExercise_5_1Dlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExercise_5_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExercise_5_1Dlg::OnBnClickedLoadBtn()
{
    // TODO: 在此添加控件通知处理程序代码
    setlocale(LC_CTYPE, "chs");
    CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        _T("文本文件(*.txt)|*.txt||"), this);
    TCHAR *pBuf = NULL;
    if (IDOK == fileDlg.DoModal()) {
        try {
            CFile file(fileDlg.GetPathName(), CFile::modeRead);
            int len = (int) file.GetLength();
            pBuf = new TCHAR[(len+1)*sizeof(TCHAR)];
            memset(pBuf, 0, (len+1)*sizeof(TCHAR));
            pBuf[file.Read(pBuf, len)] = _T('\0');
        }
        catch (CFileException &e) {
            TRACE(_T("File count not be opened, cause = %d\n"), e.m_cause);
        }

        SetDlgItemText(IDC_EDIT, pBuf);
        delete[] pBuf;
    }
}


void CExercise_5_1Dlg::OnBnClickedSaveBtn()
{
    // TODO: 在此添加控件通知处理程序代码
    setlocale(LC_CTYPE, "chs");

    CFileDialog fileDlg(FALSE, NULL, _T("未命名.txt"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        _T("文本文件(*.txt)|*.txt||"), this);

    CString strBuf;
    GetDlgItemText(IDC_EDIT, strBuf);

    if (IDOK == fileDlg.DoModal()) {
        try {
            CFile file(fileDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
            #ifdef _UNICODE
            WORD unicode = 0xFEFF;
            file.Write(&unicode, 2);
            #endif
            file.Write((LPCTSTR) strBuf, strBuf.GetLength()*sizeof(TCHAR));
        }
        catch (CFileException &e) {
            TRACE(_T("File count not be opened, cause = %d\n"), e.m_cause);
        }
    }
}

void CExercise_5_1Dlg::OnPopupMenuClicked(UINT uId)
{
    CEdit *pEdt = (CEdit*) GetDlgItem(IDC_EDIT);
    switch (uId) {
        case ID_FILE_LOAD1: OnBnClickedLoadBtn(); break;
        case ID_FILE_SAVE1: OnBnClickedSaveBtn(); break;
        case ID_FILE_EXIT1: OnOK(); break;
        case ID_EDIT_UNDO1: pEdt->Undo(); break;
        case ID_EDIT_CUT1: pEdt->Cut(); break;
        case ID_EDIT_COPY1: pEdt->Copy(); break;
        case ID_EDIT_PASTE1: pEdt->Paste(); break;
        case ID_EDIT_SELECTALL1: pEdt->SetSel(0, -1); break;
        case ID_HELP_ABOUT1: MessageBox(_T("简易记事本程序 v1.0")); break;
        default: break;
    }
}

void CExercise_5_1Dlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
    CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

    // TODO: 在此处添加消息处理程序代码
    CEdit *pEdit = (CEdit*) GetDlgItem(IDC_EDIT);
    switch (nIndex) {
    case 1:
        {
            pPopupMenu->EnableMenuItem(ID_EDIT_UNDO1,
                pEdit->CanUndo() ? MF_ENABLED : MF_GRAYED);

            int iSelBeg, iSelEnd;
            pEdit->GetSel(iSelBeg, iSelEnd);
            int iState = iSelBeg == iSelEnd ? MF_GRAYED : MF_ENABLED;

            pPopupMenu->EnableMenuItem(ID_EDIT_CUT1, iState);
            pPopupMenu->EnableMenuItem(ID_EDIT_COPY1, iState);

            pPopupMenu->EnableMenuItem(ID_EDIT_PASTE1,
                IsClipboardFormatAvailable(CF_TCHARTEXT) ? MF_ENABLED : MF_GRAYED);
        }
        break;

    default:
        break;
    }
}

BOOL CExercise_5_1Dlg::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
    if (TranslateAccelerator(GetSafeHwnd(), (HACCEL) m_hAccel, pMsg))
        return TRUE;

    return CDialogEx::PreTranslateMessage(pMsg);
}


void CExercise_5_1Dlg::OnSetFocus(CWnd* pOldWnd)
{
    CDialogEx::OnSetFocus(pOldWnd);

    // TODO: 在此处添加消息处理程序代码
    GetDlgItem(IDC_EDIT)->SetFocus();
}
