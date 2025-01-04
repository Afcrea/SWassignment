
// DrawCirclesDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DrawCircles.h"
#include "DrawCirclesDlg.h"
#include "afxdialogex.h"
#include "iostream"
#include "string"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <thread>

//#ifdef _UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif


#pragma region 기본 함수들

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDrawCirclesDlg 대화 상자



CDrawCirclesDlg::CDrawCirclesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRAWCIRCLES_DIALOG, pParent)
	, x1(0)
	, y1(0)
	, x2(640)
	, y2(480)
	, isTrace(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawCirclesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, x1);
	DDX_Text(pDX, IDC_EDIT_Y1, y1);
	DDX_Text(pDX, IDC_EDIT_X2, x2);
	DDX_Text(pDX, IDC_EDIT_Y2, y2);
	DDX_Check(pDX, IDC_CHECK_TRACE, isTrace);
}

BEGIN_MESSAGE_MAP(CDrawCirclesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONUP()
ON_COMMAND(ID_MENU_THREECIRCLES, &CDrawCirclesDlg::OnMenuThreecircles)
ON_BN_CLICKED(IDC_BTN_DRAW, &CDrawCirclesDlg::OnBnClickedBtnDraw)
ON_BN_CLICKED(IDC_BTN_ACTION, &CDrawCirclesDlg::OnBnClickedBtnAction)
ON_BN_CLICKED(IDC_CHECK_TRACE, &CDrawCirclesDlg::OnBnClickedCheckTrace)
ON_BN_CLICKED(IDC_BTN_LOAD, &CDrawCirclesDlg::OnBnClickedBtnLoad)
END_MESSAGE_MAP()


// CDrawCirclesDlg 메시지 처리기

BOOL CDrawCirclesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	Init();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDrawCirclesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDrawCirclesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDrawCirclesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CDrawCirclesDlg::PreTranslateMessage(MSG* pMsg)
{   
	
	return CDialogEx::PreTranslateMessage(pMsg);
}
#pragma endregion

// 초기화 함수 생성자 내부에 선언됨
void CDrawCirclesDlg::Init() {
	srand(static_cast<unsigned>(time(0)));
	nRadius = 10;
	isAction = false;
	nImageWidth = 0;
	nImageHeight = 40;
	isNotFound = false;
}

// 메뉴 바 : 세점으로 원 그리기 다이얼로그 생성
void CDrawCirclesDlg::OnMenuThreecircles()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_pMyDialog == nullptr) // 다이얼로그가 이미 열려 있는지 확인
	{
		m_pMyDialog = new CThreeCirclesDlg;
		m_pMyDialog->MainDlg = this;
		m_pMyDialog->Create(IDD_THREECIRCLES_DIALOG, this); // 다이얼로그 리소스 ID 사용
		m_pMyDialog->ShowWindow(SW_SHOW);        // 다이얼로그 표시
	}
}

// 드로우 버튼 이벤트
void CDrawCirclesDlg::OnBnClickedBtnDraw()
{
	UpdateData();

	SetBackgroundImage();

	nRadius = SetRadius();

	drawCircle(fm, x1, y1, 255);

	UpdateDisplay();

	SaveCirclesImage();
}

// 기본 바탕 이미지 
void CDrawCirclesDlg::SetBackgroundImage() {
	if (m_image) {
		m_image.Destroy();
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nWidth = x2;
	int nHeight = y2;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0, nWidth * nHeight);
}

// 반지름 설정 함수
int CDrawCirclesDlg::SetRadius() {

	int temp = rand() % 50;

	while (temp < 20) {
		temp = rand() % 50;
	}

	return temp;
}

// 현재 이미지 그리기 함수
void CDrawCirclesDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, nImageWidth, nImageHeight);
}

// 원 그리기 함수
void CDrawCirclesDlg::drawCircle(unsigned char* fm, int x, int y, int color)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();


	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (x + nRadius + nRadius >= x2 || y + nRadius + nRadius >= y2) {
				isAction = false;
				return;
			}
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius)) {
				
				fm[j * nPitch + i] = color;
			}
				
		}
	}
}

// 원인지 판단
bool CDrawCirclesDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}

// 원 무브 함수
void CDrawCirclesDlg::moveCircle()
{
	nSttX = x1;
	nSttY = y1;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	//int nRadius = 20;

	if (isTrace) {
		if (m_image) {
			for (int i = 0; i < nHeight; i++) {
				for (int j = 0; j < nWidth; j++) {
					fm[i * nPitch + j] = 0;
				}
			}
		}
	}

	//std::cout << "x1 : " << x1 << " y1 : " << y1 << "radius : " << nRadius << std::endl;

	drawCircle(fm, ++x1, ++y1, 0xff);

	UpdateDisplay();

	SaveCirclesImage();
}

// 액션 버튼
void CDrawCirclesDlg::OnBnClickedBtnAction()
{
	if (!m_image) {
		AfxMessageBox(_T("Draw 를 눌러 이미지를 생성하세요. "));
		return;
	}

	isAction = !isAction;

	CButton* pButton = (CButton*)GetDlgItem(IDC_BTN_ACTION);

	if (isAction) {

		pButton->SetWindowText(_T("Stop"));

		std::thread([this]()
			{
				while(isAction)
				{
					moveCircle(); // 작업 수행
					std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 10ms 대기
				}
				CButton* pButton = (CButton*)GetDlgItem(IDC_BTN_ACTION);
				pButton->SetWindowText(_T("Action"));
			}).detach(); // 스레드 분리
	}
	else {
		pButton->SetWindowText(_T("Action"));
	}
	
}

// 체크 박스
void CDrawCirclesDlg::OnBnClickedCheckTrace()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	isTrace = !isTrace;
}

// 이미지 저장
void CDrawCirclesDlg::SaveCirclesImage() {
	// 실행 파일 경로 가져오기
	if (!savedPath.IsEmpty()) {
		int dotPos = savedPath.ReverseFind(_T('.'));
		if (dotPos != -1) {
			// "save" 부분 추출
			CString basePath = savedPath.Left(dotPos);

			// 숫자를 추가
			CString strSuffix;
			strSuffix.Format(_T("%d"), nSttX);
			basePath += strSuffix;

			// 확장자 추가
			basePath += _T(".bmp");

			// 저장
			if (m_image.Save(basePath) == S_OK) {
				//std::wcout << static_cast<LPCTSTR>(basePath) << std::endl; // 저장된 경로 출력
			}
			else {
				AfxMessageBox(_T("이미지 저장에 실패했습니다."));
			}
		}
		else {
			AfxMessageBox(_T("경로에 확장자가 없습니다."));
		}
		return;
	}

	// 경로 입력받기 (파일 저장 대화 상자 사용)
	CFileDialog fileDlg(FALSE, _T("bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), this);

	if (fileDlg.DoModal() == IDOK) {
		// 선택한 경로 저장
		savedPath = fileDlg.GetPathName();

		// 이미지 저장
		m_image.Save(savedPath);
	}
	else {
		AfxMessageBox(_T("파일 저장이 취소되었습니다."));
	}
}

// 이미지 로드
void CDrawCirclesDlg::LoadCirclesImage() {
	if (m_image) {
		m_image.Destroy();
	}

	// 경로 입력받기 (파일 열기 대화 상자 사용)
	CFileDialog fileDlg(TRUE, _T("bmp"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		_T("Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), this);

	if (fileDlg.DoModal() == IDOK) {
		CString filePath = fileDlg.GetPathName(); // 선택한 파일 경로 가져오기
		savedPath = filePath;
		// 이미지 로드
		if (m_image.Load(filePath) == S_OK) {
			fm = (unsigned char*)m_image.GetBits();
			UpdateDisplay();
			FindExtremeCircle();
		}
		else {
			AfxMessageBox(_T("이미지 로드에 실패했습니다."));
		}
	}
	else {
		AfxMessageBox(_T("파일 열기가 취소되었습니다."));
	}
}

// 로드 버튼
void CDrawCirclesDlg::OnBnClickedBtnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LoadCirclesImage();
}

// 원 찾기
void CDrawCirclesDlg::FindExtremeCircle()
{
	if (!m_image.IsNull()) {
		int width = m_image.GetWidth();
		int height = m_image.GetHeight();
		int pitch = m_image.GetPitch();
		BYTE* pBits = (BYTE*)m_image.GetBits();

		// 이미지 유효성 검사
		if (m_image.GetBPP() != 8) {
			AfxMessageBox(_T("이미지가 8비트 포맷이 아닙니다."));
			return;
		}

		if (!pBits) {
			AfxMessageBox(_T("이미지 데이터를 읽을 수 없습니다."));
			return;
		}

		// 원 탐지
		int topX = 0, topY = 0;
		int leftX = 0, leftY = 0;
		int rightX = 0, rightY = 0;
		int bottomX = 0, bottomY = 0;

		int nPitch = m_image.GetPitch();

		CalCircle(nPitch, height, width, &topX, &topY, &leftX, &leftY, &rightX, &rightY, &bottomX, &bottomY);

		if (isNotFound) {
			AfxMessageBox(_T("원이 없는 이미지 입니다."));
			return;
		}

		int centerX = topX;
		int centerY = leftY;
		int radius = (topX - leftX);

		centerX = bottomX;
		centerY = rightY;
		radius = (bottomX - rightX);
		x1 = centerX - abs(radius);
		y1 = centerY - abs(radius);
		nRadius = abs(radius);

		/*std::cout << topX << ", " << topY << std::endl;
		std::cout << leftX << ", " << leftY << std::endl;
		std::cout << rightX << ", " << rightY << std::endl;
		std::cout << bottomX << ", " << bottomY << std::endl;*/

		fm[centerY * nPitch + centerX] = 0;
		fm[centerY * nPitch + centerX+1] = 0;
		fm[centerY * nPitch + centerX-1] = 0;
		fm[(centerY + 1) * nPitch + centerX] = 0;
		fm[(centerY + 1) * nPitch + centerX + 1] = 0;
		fm[(centerY + 1) * nPitch + centerX - 1] = 0;
		//fm[(centerY - 1) * nPitch + centerX] = 0;
		fm[(centerY - 1) * nPitch + centerX + 1] = 0;
		fm[(centerY - 1) * nPitch + centerX - 1] = 0;


		UpdateDisplay();

		// 결과 출력
		CString message;
		message.Format(_T("원의 중심: (%d, %d), 반지름: %d"), centerX, centerY, radius);
		AfxMessageBox(message);
	}
	else {
		AfxMessageBox(_T("이미지가 로드되지 않았습니다."));
	}
}

// 찾은 원의 반지름, 중심 계산
void CDrawCirclesDlg::CalCircle(int nPitch, int height, int width, int* topX, int* topY, int* leftX, int* leftY, int* rightX, int* rightY, int* bottomX, int* bottomY) {
	
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (fm[j * nPitch + i] == 255) {

				*topX = i;
				*topY = j;

				i = width+1;
				j = height+1;
				break;
			}
		}
		if (j == height) {
			isNotFound = true;
			return;
		}
	}

	int find = 0;

	for (int i = *topX; i < width; i++) {
		find++;
		if (fm[*topY * nPitch + i] == 0) {
			*topX += find / 2;
			break;
		}
	}

	for (int j = 0; j < width; j++) {
		for (int i = 0; i < height; i++) {
			if (fm[i * nPitch + j] == 255) {

				*leftX = j;
				*leftY = i;

				i = height;
				j = width;
				break;
			}
		}
	}

	find = 0;

	for (int i = *leftY; i < height; i++) {
		find++;
		if (fm[i * nPitch + *leftX] == 0) {
			*leftY += find / 2;
			break;
		}
	}

	for (int j = height-1; j > 0; j--) {
		for (int i = width-1; i > 0; i--) {
			if (fm[j * nPitch + i] == 255) {

				*bottomX = i;
				*bottomY = j;

				i = 0;
				j = 0;

				break;
			}
		}
	}

	find = 0;

	for (int i = *bottomX; i > 0; i--) {
		find++;
		if (fm[*bottomY * nPitch + i] == 0) {
			*bottomX -= find / 2;
			break;
		}
	}

	for (int j = width-1; j > 0; j--) {
		for (int i = height-1; i > 0; i--) {
			if (fm[i * nPitch + j] == 255) {

				*rightX = j;
				*rightY = i;

				i = 0;
				j = 0;
				break;
			}
		}
	}

	find = 0;

	for (int i = *rightY; i > 0; i--) {
		find++;
		if (fm[i * nPitch + *rightX] == 0) {
			*rightY -= find / 2;
			break;
		}
	}
}


