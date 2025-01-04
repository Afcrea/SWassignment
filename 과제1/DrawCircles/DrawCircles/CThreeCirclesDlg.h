#pragma once

class CDrawCirclesDlg;

// CThreeCirclesDlg 대화 상자

class CThreeCirclesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThreeCirclesDlg)

public:
	CThreeCirclesDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CThreeCirclesDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THREECIRCLES_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CDrawCirclesDlg* MainDlg;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

	int m_ClickCount = 0; // 클릭 카운트 체크
	CPoint m_Points[3];  // 클릭된 위치

	CPoint m_Center; // 3점으로 인한 원의 중심
	int m_Radius; // 3점으로 인한 원의 반지름

	void CalculateCircle(); // 3점으로 원 계산
	bool IsPointNear(const CPoint& p1, const CPoint& p2, int tolerance); // 점 근처에 마우스가 있는지 체크
	
};
