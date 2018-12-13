// Thread.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Givedata.h"
#include "Thread.h"
#include "Mywnd.h"


// CThread

IMPLEMENT_DYNCREATE(CThread, CWinThread)

CThread::CThread()
{
}

CThread::~CThread()
{
}

BOOL CThread::InitInstance()
{
	// TODO:  ���⿡�� �� �����忡 ���� �ʱ�ȭ�� �����մϴ�.
	//������ ������ ��ü�� �������� ���� 

	CRuntimeClass* pRuntimeClass = RUNTIME_CLASS(CMywnd);

	CObject* pObject = pRuntimeClass->CreateObject();

	// ��ü�� ���������� �����ߴ��� ���� Ȯ�� 

	ASSERT(pObject->IsKindOf(RUNTIME_CLASS(CMywnd)));

	// ������ ������ ��ü�� �ּҸ� ������ ��, �����찡 ȭ�鿡 ���̵��� �Ѵ�. 

	m_pMainWnd = (CWnd *)pObject;

	m_pMainWnd->ShowWindow(SW_SHOW);

	m_pMainWnd->UpdateWindow();

	return TRUE;
}

int CThread::ExitInstance()
{
	// TODO:  ���⿡�� �� �����忡 ���� ������ �����մϴ�.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThread, CWinThread)
END_MESSAGE_MAP()


// CThread �޽��� ó�����Դϴ�.
