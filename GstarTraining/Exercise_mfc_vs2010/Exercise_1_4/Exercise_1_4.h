
// Exercise_1_4.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExercise_1_4App:
// �йش����ʵ�֣������ Exercise_1_4.cpp
//

class CExercise_1_4App : public CWinApp
{
public:
	CExercise_1_4App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExercise_1_4App theApp;