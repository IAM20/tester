// Mywnd.cpp : ���� �����Դϴ�.
//
#include <stdlib.h>
#include "stdafx.h"
#include "Givedata.h"
#include "Mywnd.h"
#include "ChildView.h"
#pragma comment(lib, "winmm")
#include <mmsystem.h>

// CMywnd

IMPLEMENT_DYNCREATE(CMywnd, CFrameWnd)

CMywnd::CMywnd()
{
	//UI �����带 Rect ��ǥ�� ���� �������ش�.
	CRect Rect = { 800, 100, 1800, 600 };
	Create(NULL, _T("Climate"), WS_POPUPWINDOW | WS_CAPTION, Rect);
}

CMywnd::~CMywnd()
{
}


BEGIN_MESSAGE_MAP(CMywnd, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMywnd �޽��� ó�����Դϴ�.


void CMywnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CFrameWnd::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CBitmap Clim;
	BITMAP bmpinfo;
	CBitmap *OldBmp;
	COLORREF colorkey = RGB(255, 255, 255); // ��� ����ȭ
	bitmap[1].GetBitmap(&bmpinfo);
	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc); // �޸𸮿� BMP�� ����
	
	OldBmp = dcmem.SelectObject(&bitmap[aniBmpCount]);
	bitmap[aniBmpCount].GetBitmap(&bmpinfo);
	dc.BitBlt(10, 10, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
	dcmem.SelectObject(&OldBmp);
	
	if (aniBmpCount > 8) {
		// ������ ���� BMP ������ �����´�.
		if (target[1]._Weather == _T("���� ����")) Clim.LoadBitmap(IDB_BITMAP8);
		else if (target[1]._Weather == _T("��")) Clim.LoadBitmap(IDB_BITMAP9);
		else if (target[1]._Weather == _T("����")) Clim.LoadBitmap(IDB_BITMAP11);
		else if (target[1]._Weather == _T("��")) Clim.LoadBitmap(IDB_BITMAP12);
		else if (target[1]._Weather == _T("�帲")) Clim.LoadBitmap(IDB_BITMAP13);
		else if (target[1]._Weather == _T("���� ����")) Clim.LoadBitmap(IDB_BITMAP14);
		else Clim.LoadBitmap(IDB_BITMAP10); // ����
		OldBmp = dcmem.SelectObject(&Clim);
		Clim.GetBitmap(&bmpinfo);
		// ����ȭ bmp ���, ����κ��� ����ȭ�Ǿ�, ���󿡸��� ǥ���� �ȿ� ������ ��.
		dc.TransparentBlt(150, 35, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, colorkey);
		dcmem.SelectObject(&OldBmp);
	}
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	CRect rect;
	rect.SetRect(550, 100, 800, 800);
	CFont cFont;
	cFont.CreateFont(25,                     // ���ڳ���
		10,                     // ���ڳʺ�
		0,                      // ��°���
		0,                      // ���� �������ǰ���
		FW_HEAVY,              // ���ڱ���
		FALSE,                  // Italic ���뿩��
		FALSE,                  // �������뿩��
		FALSE,                  // ��Ҽ����뿩��
		DEFAULT_CHARSET,       // ���ڼ�����
		OUT_DEFAULT_PRECIS,    // ������е�
		CLIP_DEFAULT_PRECIS,   // Ŭ�������е�
		DEFAULT_QUALITY,       // ��¹���ǰ��
		DEFAULT_PITCH,         // �۲�Pitch
		_T("�������")           // �۲�
	);
	// DC��CFont Object ����

	dc.SelectObject(cFont);
	dc.SetBkMode(TRANSPARENT);            //���� ��� �����ϰ�
	dc.SetTextColor(RGB(0, 0, 0));         //���ڻ� ����

	int i, drawY = 100;
	CString str[7];
	str[0] = _T("�̸�:       ") + target[1]._Name;
	str[1] = _T("����:       ") + target[1]._Humidity;
	str[2] = _T("����Ȯ��: ") + target[1]._Rain;
	str[3] = _T("��ձ��: ") + target[1]._TempAve;
	str[4] = _T("�ð�:       ") + target[1]._Time;
	str[5] = _T("ǳ��:       ") + target[1]._Wd;
	str[6] = _T("ǳ��:       ") + target[1]._Ws;
	dc.SetTextColor(RGB(0, 0, 0));
	for (i = 0; i <= 6; i++) {
		rect.SetRect(530, drawY, 950, 800);
		dc.DrawText(str[i], &rect, NULL);
		drawY = drawY + 20;
	}

	dcmem.DeleteDC();
}


void CMywnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	AfxEndThread(0); // UI ������ ����
	CFrameWnd::OnLButtonDown(nFlags, point);
}

int CMywnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) 
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	int i = 0;
	aniBmpCount = 0;
	// ���󿡸� �ִϸ��̼� BMP ������ ����
	bitmap[i++].LoadBitmap(IDB_BITMAP2);
	bitmap[i++].LoadBitmap(IDB_BITMAP3);
	bitmap[i++].LoadBitmap(IDB_BITMAP4);
	bitmap[i++].LoadBitmap(IDB_BITMAP5);
	bitmap[i++].LoadBitmap(IDB_BITMAP6);
	bitmap[i++].LoadBitmap(IDB_BITMAP7);
	bitmap[i++].LoadBitmap(IDB_BITMAP15);
	bitmap[i++].LoadBitmap(IDB_BITMAP16);
	bitmap[i++].LoadBitmap(IDB_BITMAP17);
	bitmap[i++].LoadBitmap(IDB_BITMAP18);
	bitmap[i++].LoadBitmap(IDB_BITMAP19);
	bitmap[i++].LoadBitmap(IDB_BITMAP20);
	bitmap[i++].LoadBitmap(IDB_BITMAP21);
	bitmap[i++].LoadBitmap(IDB_BITMAP22);
	bitmap[i++].LoadBitmap(IDB_BITMAP23);

	PlaySound(L"Doraemon.wav", NULL, SND_ASYNC); // WAV ���� ���

	SetTimer(0, 100, NULL); // Ÿ�̸� ����
	return 0;
}


void CMywnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	aniBmpCount++; // �ִϸ��̼� ȿ���� ī��Ʈ���־ ����
	Invalidate(FALSE); // ��ȿȭ
	if (aniBmpCount == 14) KillTimer(0); // �ִϸ��̼��� ���� �� Ÿ�̸� ����
	CFrameWnd::OnTimer(nIDEvent);
}

BOOL CMywnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
	GetClientRect(rect);
	//�׶��̼� ȿ���� �������
	int nWidth = rect.Width() - 7;
	int nHeight = rect.Height();
	int nRMax = 254;
	int nGMax = 254;
	int nBMax = 254;
	int nRMin = 50;
	int nGMin = 205;
	int nBMin = 50;
	int nRDiff = nRMax - nRMin;
	int nGDiff = nGMax - nGMin;
	int nBDiff = nBMax - nBMin;

	CRect rcTemp;
	for (int i = 0; i < nHeight; ++i)
	{

		rcTemp.SetRect(0, i, nWidth, i + 1);
		pDC->FillSolidRect(&rcTemp, RGB(
			nRMax - MulDiv(i, nRDiff, nHeight),
			nGMax - MulDiv(i, nGDiff, nHeight),
			nBMax - MulDiv(i, nBDiff, nHeight)));
	}
	return TRUE;
}
