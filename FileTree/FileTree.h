
// FileTree.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// FileTreeApp:
// See FileTree.cpp for the implementation of this class
//

class FileTreeApp : public CWinApp
{
public:
	FileTreeApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern FileTreeApp theApp;
