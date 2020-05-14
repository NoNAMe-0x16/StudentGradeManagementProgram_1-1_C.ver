#pragma once

extern int DataUpdate();
extern int DataModify();

// DataInput 대화 상자

class DataInput : public CDialogEx
{
	DECLARE_DYNAMIC(DataInput)

public:
	DataInput(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DataInput();

	int GetName(CString* NameBuf);
	int GetStid(CString* StidBuf);
	int GetKorScore();
	int GetEngScore();
	int GetMatScore();
	void SetMode(int mode);
	int SetName(CString StrName);
	int SetStid(CString StrStid);
	int SetKorScore(CString StrKorScore);
	int SetEngScore(CString StrEngScore);
	int SetMatScore(CString StrMatScore);

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATAINPUT };
#endif


private:
	virtual void OnOK() {};


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EngEdit;
	CEdit m_KorEdit;
	CEdit m_MatEdit;
	CEdit m_NameEdit;
	CEdit m_StidEdit;

	CString m_EngEditInit;
	CString m_KorEditInit;
	CString m_MatEditInit;
	CString m_NameEditInit;
	CString m_StidEditInit;
	int m_Mode; // 0 이면 추가모드, 1이면 수정모드.

	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
