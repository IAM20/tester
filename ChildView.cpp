// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "Givedata.h"
#include "ChildView.h"
#include <urlmon.h>
#include <windows.h>
#include <stdlib.h>
#include <locale.h>
#include "Markup.h"
#include "Mywnd.h"
#include "Thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define		_CITY_COUNT		17

#define		SEOUL			0
#define		INCHEON			1
#define		SUWON			2
#define		CHUNCHEON		3
#define		CHEONGJU		4
#define		HONGSEONG		5
#define		GWANGJU			6
#define		DAEJEON			7
#define		JEONJU			8
#define		MOHPO			9
#define		DAEGU			10
#define		ULSAN			11
#define		POHANG			12
#define		CHANGWON		13
#define		BUSAN			14
#define		JEJU			15
#define		DOKDO			16

#define		X_DOKDO			500
#define		Y_JEJU			650

CMarkup xml;
inform cityInform[_CITY_COUNT];
inform target[2];

//////////////////////////////////////

void GetURL(CString _city) {
	printf("URLDownloadToFile test function.\n");

	TCHAR* url = _city.GetBuffer(_city.GetLength());

	printf("Url: %S\n", url);

	TCHAR path[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, path);

	wsprintf(path, TEXT("%s\\TestXML.xml"), path);

	printf("Path: %S\n", path);

	HRESULT res = URLDownloadToFile(NULL, url, path, 0, NULL);

	if (res == S_OK) {
		printf("Ok\n");
	}
	else if (res == E_OUTOFMEMORY) {
		printf("Buffer length invalid, or insufficient memory\n");
	}
	else if (res == INET_E_DOWNLOAD_FAILURE) {
		printf("URL is invalid\n");
	}
	else {
		printf("Other error: %d\n", res);
	}
	return;
}

void CountryInform(CMarkup* _xml) {
	_tsetlocale(LC_ALL, _T(""));

	CString strFileName = MCD_T("C:\\Users\\USER\\Documents\\Visual Studio 2015\\Projects\\Givedata\\Givedata\\TestXML.XML");
	bool state = (*_xml).Load(strFileName);

	MCD_STR strDoc;
	bool state2 = CMarkup::ReadTextFile(MCD_T("TestXML.XML"), strDoc);
	if (CMarkup::ReadTextFile(MCD_T("TestXML.XML"), strDoc) == false)
	{
		return;
	}
	(*_xml).SetDoc(strDoc);

	CString str[10];
	int i = 0;

	inform city;
}

void CityInform(CMarkup* _xml, inform* _city) {
	(*_xml).FindElem(_T("rss"));                  //rss 정보를 찾는다.
	(*_xml).IntoElem();                           //rss 안의 내용 확인
	(*_xml).FindElem(_T("channel"));               //channel 정보를 찾는다.
	(*_xml).IntoElem();                           //rss->channel 안의 내용 확인
	(*_xml).FindElem(_T("pubDate"));
	(*_city)._Time = (*_xml).GetData();
	(*_xml).FindElem(_T("item"));
	(*_xml).IntoElem();
	(*_xml).FindElem(_T("category"));
	(*_city)._Name = (*_xml).GetData();
	(*_xml).FindElem(_T("description"));
	(*_xml).IntoElem();
	(*_xml).FindElem(_T("body"));
	(*_xml).IntoElem();
	(*_xml).FindElem(_T("data"));
	(*_xml).IntoElem();
	(*_xml).FindElem(_T("temp"));
	(*_city)._TempAve = (*_xml).GetData() + _T(" (°C)");
	(*_xml).FindElem(_T("wfKor"));
	(*_city)._Weather = (*_xml).GetData();
	(*_xml).FindElem(_T("pop"));
	(*_city)._Rain = (*_xml).GetData() + _T(" (%)");
	(*_xml).FindElem(_T("ws"));
	(*_city)._Ws = ((*_xml).GetData()).Left(4) + _T(" (m/s)");
	(*_xml).FindElem(_T("wdKor"));
	(*_city)._Wd = (*_xml).GetData();
	(*_xml).FindElem(_T("reh"));
	(*_city)._Humidity = (*_xml).GetData() + _T(" (%)");
	return;
}

void LoadInform(inform cityInform[_CITY_COUNT]) {
	CMarkup xml;
	CString cityList[_CITY_COUNT];
	cityList[0] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=1168066000");   //서울(특별시)
	cityList[1] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=2871025000");   //인천(광역시)
	cityList[2] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4111369000");   //수원(경기도)
	cityList[3] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4211067500");   //춘천(강원도)
	cityList[4] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4311133000");   //청주(충북)
	cityList[5] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4480038000");   //홍성(충남)
	cityList[6] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=2920054000");   //광주(광역시)
	cityList[7] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=3023052000");   //대전(광역시)
	cityList[8] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4511358000");   //전주(전북)
	cityList[9] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4611056500");   //목포(전남)
	cityList[10] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=2720065000");   //대구(광역시)
	cityList[11] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=3114056000");   //울산(광역시)
	cityList[12] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4711334000");   //포항(경북)
	cityList[13] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4812552000");   //창원(경남)
	cityList[14] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=2644058000");   //부산(광역시)
	cityList[15] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=5013025300");   //제주(섬)
	cityList[16] = MCD_T("http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4794033000");   //독도(섬)

	for (int i = 0; i < _CITY_COUNT; i++){
		GetURL(cityList[i]); // URL을 받아와준다
		CountryInform(&xml); // XML로 부터 모든 지역의 정보를 받아온다.
		CityInform(&xml, &(cityInform[i])); // CountryInform으로부터 SearchCity한 지역의 정보를 target에 저장해준다.
	}

	return;
}

void SearchCity(COLORREF Red, COLORREF Green, CPoint point) {
	if (Red == 243) target[0] = cityInform[0];
	else if (Red == 244) target[0] = cityInform[1];
	else if (Red == 249) target[0] = cityInform[2];
	else if (Red == 163) target[0] = cityInform[3];
	else if ((Red == 196) && (point.x < X_DOKDO)) target[0] = cityInform[4];
	else if ((Red == 255) && (Green != 255)) target[0] = cityInform[5];
	else if ((Red == 161) && (point.y < Y_JEJU)) target[0] = cityInform[6];
	else if (Red == 130) target[0] = cityInform[7];
	else if (Red == 109) target[0] = cityInform[8];
	else if (Red == 246) target[0] = cityInform[9];
	else if (Red == 96) target[0] = cityInform[10];
	else if (Red == 86) target[0] = cityInform[11];
	else if (Red == 125) target[0] = cityInform[12];
	else if (Red == 122) target[0] = cityInform[13];
	else if (Red == 68) target[0] = cityInform[14];
	else if ((Red == 161) && (point.y > Y_JEJU)) target[0] = cityInform[15];
	else if ((Red == 196) && (point.x > X_DOKDO)) target[0] = cityInform[16];

	return;
}

UINT WolkerThread(LPVOID second)
{
	int val = (int) second;
	int i;
	while (1)
	{
		for(i=1;i<=60;i++) Sleep(val); // 1시간 대기해줌

		LoadInform(cityInform); //1시간마다 정보를 불러와줌 
	}

	return 0;
}
// CChildView

CChildView::CChildView()
{	
	int val = 1000;
	LoadInform(cityInform);
	WThread = AfxBeginThread(WolkerThread,(LPVOID)val); // 작업자 쓰레드 생성
	WThread-> m_bAutoDelete = FALSE; // 작업자 쓰레드가 사라지지 않게 함.
}

CChildView::~CChildView()
{
	delete WThread; // 소멸자 발생시 작업자 스레드 제거
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	// 지도를 화면에 출력한다.
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);
	CDC dcmem; 
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&bitmap); //메모리에 BMP를 저장
 	dc.StretchBlt(10, 10, bmpinfo.bmWidth * 2, bmpinfo.bmHeight * 2, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY); // 화면에 출력
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnLButtonDown(nFlags, point);

	CClientDC dc(this);

	COLORREF Pixel = dc.GetPixel(point.x, point.y);

	if (Pixel != 0xffffff) {
		// 지도를 좌클릭 하였을 때, UI 쓰레드 생성
		AfxBeginThread(RUNTIME_CLASS(CThread));
		target[1] = target[0];
	}
	return;
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnMouseMove(nFlags, point);

	CClientDC dc(this);

	COLORREF Pixel = dc.GetPixel(point.x, point.y); //RGB값 가져온다.
	COLORREF Red = GetRValue(Pixel);
	COLORREF Green = GetGValue(Pixel);

	if (Pixel != 0xffffff) {
		SearchCity(Red, Green, point);
		CBitmap Clim;
		BITMAP bmpinfo;
		CDC dcmem1;
		if (target[0]._Weather == _T("구름 조금")) Clim.LoadBitmap(IDB_MINCLOUDY);
		else if (target[0]._Weather == _T("눈")) Clim.LoadBitmap(IDB_SNOW);
		else if (target[0]._Weather == _T("맑음")) Clim.LoadBitmap(IDB_SUNNY);
		else if (target[0]._Weather == _T("비")) Clim.LoadBitmap(IDB_RAIN);
		else if (target[0]._Weather == _T("흐림")) Clim.LoadBitmap(IDB_BAD);
		else if (target[0]._Weather == _T("구름 많음")) Clim.LoadBitmap(IDB_CLOUDY);
		else   Clim.LoadBitmap(IDB_DOUBLE);

		Clim.GetBitmap(&bmpinfo);
		COLORREF colorkey = RGB(255, 255, 255);
		dcmem1.CreateCompatibleDC(&dc);
		dcmem1.SelectObject(&Clim);
		CBitmap bitmap;
		bitmap.LoadBitmapW(IDB_BITMAP1);
		BITMAP bmpinfo1;
		bitmap.GetBitmap(&bmpinfo1);
		CDC dcmem;
		dcmem.CreateCompatibleDC(&dc);
		dcmem.SelectObject(&bitmap);
		dc.StretchBlt(10, 10, bmpinfo1.bmWidth * 2, bmpinfo1.bmHeight * 2, &dcmem, 0, 0, bmpinfo1.bmWidth, bmpinfo1.bmHeight, SRCCOPY);

		dc.StretchBlt(point.x + 10, point.y + 10, bmpinfo.bmWidth*0.8, bmpinfo.bmHeight*0.8, &dcmem1, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	}
	else {
		CBitmap bitmap;
		bitmap.LoadBitmapW(IDB_BITMAP1);
		BITMAP bmpinfo1;
		bitmap.GetBitmap(&bmpinfo1);
		CDC dcmem;
		dcmem.CreateCompatibleDC(&dc);
		dcmem.SelectObject(&bitmap);
		dc.StretchBlt(10, 10, bmpinfo1.bmWidth * 2, bmpinfo1.bmHeight * 2, &dcmem, 0, 0, bmpinfo1.bmWidth, bmpinfo1.bmHeight, SRCCOPY);
	}

}
