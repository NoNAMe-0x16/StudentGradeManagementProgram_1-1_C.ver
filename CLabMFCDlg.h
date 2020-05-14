
// CLabMFCDlg.h: 헤더 파일
//

#pragma once
#include "DataInput.h"


int DataUpdate();

// CCLabMFCDlg 대화 상자
class CCLabMFCDlg : public CDialogEx
{
// 생성입니다.
public:
	CCLabMFCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	DataInput m_DataInput;

	CFont m_ProfileFont;
	FILE* m_SaveFile;
	FILE* m_TxtFile;
	FILE* m_ExcelFile;
	FILE* m_HTMLFile;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLABMFC_DIALOG };
#endif

	int DataUpdate();
	int DataModify();
	char Grade(int X);
	int GetRank(int X);
	int SetRank();
	int m_nSortedColumn;  //SORTING하기위한 멤버 변수
	BOOL m_bAscending;  //''

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


private:
	virtual void OnOK() {};

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
	afx_msg void OnBnClickedDatainputB();
//	CMFCMenuButton m_MenuB;
	afx_msg void OnBnClickedSummaryL();
	CListCtrl m_DataList;
	afx_msg void OnBnClickedDelete();
	afx_msg void OnLvnItemchangedDatalist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickDatalist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedFix();
	afx_msg void OnBnClickedSearch();

	CComboBox m_SearchMenu;
	CEdit m_SearchEdit;
	afx_msg void OnBnClickedSearchb();
	afx_msg void OnBnClickedFilesave();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedTxtb();
	afx_msg void OnBnClickedExcelb();
	afx_msg void OnBnClickedHtmlb();
};


