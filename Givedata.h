
// Givedata.h : Givedata ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CGivedataApp:
// �� Ŭ������ ������ ���ؼ��� Givedata.cpp�� �����Ͻʽÿ�.
//

class CGivedataApp : public CWinApp
{
public:
	CGivedataApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGivedataApp theApp;
