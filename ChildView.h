
// ChildView.h : CChildView Ŭ������ �������̽�
//


#pragma once


// CChildView â

class CChildView : public CWnd
{
// �����Դϴ�.
public:
	CChildView();

// Ư���Դϴ�.
public:
// �۾��Դϴ�.
public:
	CWinThread* WThread;
// �������Դϴ�.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CChildView();

	// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
typedef struct inform {
	CString _Time;        //pubData   �ð�
	CString _Name;        //category   �����̸�
	CString _TempAve;     //temp      ��ձ��
	CString _Weather;     //wfKor      ����
	CString _Rain;        //pop      ����Ȯ��
	CString _Ws;          //ws      ǳ��
	CString _Wd;          //wdKor      ǳ��
	CString _Humidity;    //reh      ����
}inform;
extern inform target[2]; // ���� ����ü ����
