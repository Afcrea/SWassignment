
// DrawCirclesDlg.h: 헤더 파일
//

#pragma once
#include "CThreeCirclesDlg.h"

// CDrawCirclesDlg 대화 상자
class CDrawCirclesDlg : public CDialogEx
{
private:
	CImage m_image;
	int nImageWidth;
	int nImageHeight;
// 생성입니다.
public:
	CDrawCirclesDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAWCIRCLES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	CThreeCirclesDlg* m_pMyDialog;

	afx_msg void OnMenuThreecircles();

	void Init();
	void moveCircle();
	void UpdateDisplay();
	void drawCircle(unsigned char* fm, int x, int y, int color);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	int SetRadius();
	void SetBackgroundImage();
	void SaveCirclesImage();
	void LoadCirclesImage();
	void FindExtremeCircle();
	void CalCircle(int nPitch, int height, int width, int* topX, int* topY, int* leftX, int* leftY, int* rightX, int* rightY, int* bottomX, int* bottomY);

	unsigned char* fm;

	int x1;
	int y1;
	int x2;
	int y2;

	int nSttX;
	int nSttY;

	int nRadius;

	bool isAction;

	CString savedPath;
	CString loadedPath;
	int saveTime;

	bool isNotFound;

	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	BOOL isTrace;
	afx_msg void OnBnClickedCheckTrace();
	afx_msg void OnBnClickedBtnLoad();
};
