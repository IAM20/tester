#pragma once


// CMywnd �������Դϴ�.

class CMywnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMywnd)
protected:
	CMywnd();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMywnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CBitmap bitmap[14]; // ���󿡸� �ִϸ��̼� BMP
	UINT aniBmpCount; // �ִϸ��̼� ī��Ʈ
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};