// CThreeCirclesDlg.cpp: 구현 파일
//

#include "pch.h"
#include "DrawCircles.h"
#include "afxdialogex.h"
#include "CThreeCirclesDlg.h"
#include "DrawCirclesDlg.h" 
#include "iostream"


// CThreeCirclesDlg 대화 상자

IMPLEMENT_DYNAMIC(CThreeCirclesDlg, CDialogEx)

CThreeCirclesDlg::CThreeCirclesDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_THREECIRCLES_DIALOG, pParent)
{

}

CThreeCirclesDlg::~CThreeCirclesDlg()
{
    if (this != nullptr)
    {
        this->DestroyWindow();
        MainDlg->m_pMyDialog = nullptr;
        
    }
}

void CThreeCirclesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CThreeCirclesDlg, CDialogEx)
    ON_BN_CLICKED(IDOK, &CThreeCirclesDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CThreeCirclesDlg::OnBnClickedCancel)
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CThreeCirclesDlg 메시지 처리기


void CThreeCirclesDlg::OnBnClickedOk()
{
    if (this != nullptr)
    {
        this->DestroyWindow();
        MainDlg->m_pMyDialog = nullptr;

    }
}


void CThreeCirclesDlg::OnBnClickedCancel()
{
    if (this != nullptr)
    {
        this->DestroyWindow();
        MainDlg->m_pMyDialog = nullptr;
    }
}


void CThreeCirclesDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_ClickCount < 3)
	{
		for (int i = 0; i < m_ClickCount; i++) {
			if (m_Points[i] == point) {
				AfxMessageBox(_T("error : 동일한 위치에 클릭되었습니다. !!"));
				return;
			}
		}
		m_Points[m_ClickCount] = point; // 좌표 저장
		m_ClickCount++;

		if (m_ClickCount == 3)
		{
			// 세 점을 지나는 원 계산
			CalculateCircle();
		}
		Invalidate(); // 화면 갱신
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CThreeCirclesDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)
	{
		for (int i = 0; i < 3; i++)
		{
			if (IsPointNear(point, m_Points[i], 5))
			{
				m_Points[i] = point; // 좌표 업데이트
				CalculateCircle();
				Invalidate();
				break;
			}
		}
	}
}


void CThreeCirclesDlg::OnPaint()
{
	CPaintDC dc(this);

	for (int i = 0; i < m_ClickCount; i++)
	{
		CBrush FullBrush((i == 0) ? RGB(255, 0, 0) : (i == 1) ? RGB(0, 0, 255) : RGB(0, 255, 0));

		dc.SelectObject(&FullBrush);
		dc.Ellipse(m_Points[i].x - 5, m_Points[i].y - 5, m_Points[i].x + 5, m_Points[i].y + 5);
	}

	// 세 점을 지나는 원 그리기
	if (m_ClickCount == 3)
	{
		CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&pen);

		CBrush brush;
		brush.CreateStockObject(NULL_BRUSH);

		dc.SelectObject(&brush);

		// 원의 외곽만 그리기
		CRect circleRect(
			m_Center.x - m_Radius, m_Center.y - m_Radius,
			m_Center.x + m_Radius, m_Center.y + m_Radius
		);
		dc.Ellipse(&circleRect); // 테두리만 그려짐

		// 이전 DC 설정 복원
		dc.SelectObject(pOldPen);
	}
}

bool CThreeCirclesDlg::IsPointNear(const CPoint& p1, const CPoint& p2, int tolerance)
{
	// 두 점 간의 거리 계산
	double distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

	// 거리가 허용 오차(tolerance) 이내인지 확인
	return distance <= tolerance;
}

void CThreeCirclesDlg::CalculateCircle()
{
	if (m_ClickCount < 3) return; // 좌표가 3개 미만이면 계산하지 않음

	// 세 점
	const CPoint& p1 = m_Points[0];
	const CPoint& p2 = m_Points[1];
	const CPoint& p3 = m_Points[2];

	// 세 점이 한 직선상에 있는지 확인
	int determinant = (p1.x * (p2.y - p3.y)) + (p2.x * (p3.y - p1.y)) + (p3.x * (p1.y - p2.y));
	if (determinant == 0)
	{
		AfxMessageBox(_T("세 점이 한 직선상에 있어 원을 만들 수 없습니다."));
		return;
	}

	// 중점 및 기울기 계산
	double mid1_x = (p1.x + p2.x) / 2.0;
	double mid1_y = (p1.y + p2.y) / 2.0;
	double mid2_x = (p2.x + p3.x) / 2.0;
	double mid2_y = (p2.y + p3.y) / 2.0;

	double slope1 = (p2.y - p1.y) / static_cast<double>(p2.x - p1.x);
	double slope2 = (p3.y - p2.y) / static_cast<double>(p3.x - p2.x);

	double perpSlope1 = -1.0 / slope1;
	double perpSlope2 = -1.0 / slope2;

	// 수직 이등분선 방정식 교차점 계산
	double h = ((perpSlope1 * mid1_x - mid1_y) - (perpSlope2 * mid2_x - mid2_y)) / (perpSlope1 - perpSlope2);
	double k = perpSlope1 * (h - mid1_x) + mid1_y;

	// 반지름 계산
	double radius = sqrt(pow(p1.x - h, 2) + pow(p1.y - k, 2));

	// 결과 저장
	m_Center = CPoint(static_cast<int>(h), static_cast<int>(k));
	m_Radius = static_cast<int>(radius);
}