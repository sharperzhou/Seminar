
// MfcPyDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MfcPy.h"
#include "MfcPyDlg.h"
#include "afxdialogex.h"

#include "Python.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcPyDlg 对话框



CMfcPyDlg::CMfcPyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcPyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMfcPyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_LOAD, &CMfcPyDlg::OnBnClickedBtnLoad)
    ON_BN_CLICKED(IDC_BTN_SAVE, &CMfcPyDlg::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// CMfcPyDlg 消息处理程序

BOOL CMfcPyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMfcPyDlg::OnPaint()
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
HCURSOR CMfcPyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMfcPyDlg::OnBnClickedBtnLoad()
{
    // TODO: 在此添加控件通知处理程序代码
    // Py_SetPythonHome(L".\\");
    Py_Initialize();
    if (!Py_IsInitialized()) {
        AfxMessageBox(_T("初始化Python失败"));
        return;
    }

    PyRun_SimpleString("import sys");
    PyRun_SimpleString(R"(sys.path.append('.\'))");

    auto pModule = PyImport_ImportModule("pymodule");
    if (!pModule) {
        AfxMessageBox(_T("无法导入pymodule模块"));
        return;
    }

    auto pFunc = PyObject_GetAttrString(pModule, "load");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        AfxMessageBox(_T("无法从pymodule模块中加载load函数"));
        return;
    }

    auto pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", "content.txt"));

    auto pRet = PyObject_CallObject(pFunc, pArgs);
    if (!pRet) {
        AfxMessageBox(_T("无法从应用程序当前文件夹打开content.txt文件"));
        return;
    }

    auto pRes = PyUnicode_AsUnicode(pRet);

    CString s(pRes);

    Py_Finalize();

    SetDlgItemText(IDC_EDIT, s);
}


void CMfcPyDlg::OnBnClickedBtnSave()
{
    // TODO: 在此添加控件通知处理程序代码
    // Py_SetPythonHome(L".\\");
    Py_Initialize();
    if (!Py_IsInitialized()) {
        AfxMessageBox(_T("初始化Python失败"));
        return;
    }

    PyRun_SimpleString("import sys");
    PyRun_SimpleString(R"(sys.path.append('.\'))");

    auto pModule = PyImport_ImportModule("pymodule");
    if (!pModule) {
        AfxMessageBox(_T("无法导入pymodule模块"));
        return;
    }

    auto pFunc = PyObject_GetAttrString(pModule, "save");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        AfxMessageBox(_T("无法从pymodule模块中加载save函数"));
        return;
    }

    auto pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", "content.txt"));

    CString strBuffer;
    GetDlgItemText(IDC_EDIT, strBuffer);

    PyTuple_SetItem(pArgs, 1, PyUnicode_FromWideChar(strBuffer, strBuffer.GetLength()));

    PyObject_CallObject(pFunc, pArgs);

    Py_Finalize();
}
