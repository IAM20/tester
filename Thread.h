#pragma once



// CThread

class CThread : public CWinThread
{
	DECLARE_DYNCREATE(CThread)

protected:
	CThread();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


