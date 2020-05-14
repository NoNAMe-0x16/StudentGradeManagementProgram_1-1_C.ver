// DataInput.cpp: 구현 파일
//

#include "pch.h"
#include "CLabMFC.h"
#include "DataInput.h"
#include "afxdialogex.h"



// DataInput 대화 상자

IMPLEMENT_DYNAMIC(DataInput, CDialogEx)

DataInput::DataInput(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DATAINPUT, pParent)
{

}

DataInput::~DataInput()
{
}

void DataInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ENGEDIT, m_EngEdit);
	DDX_Control(pDX, IDC_KOREDIT, m_KorEdit);
	DDX_Control(pDX, IDC_MATEDIT, m_MatEdit);
	DDX_Control(pDX, IDC_NAMEEDIT, m_NameEdit);
	DDX_Control(pDX, IDC_STIDEDIT, m_StidEdit);
}


BEGIN_MESSAGE_MAP(DataInput, CDialogEx)
	ON_BN_CLICKED(IDOK, &DataInput::OnBnClickedOk)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// DataInput 메시지 처리기


void DataInput::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	if (m_Mode == 0)
		int rtn = DataUpdate();
	else if (m_Mode == 1)
		int rtn = DataModify();

	CDialogEx::OnOK();
}

int DataInput::GetName(CString *NameBuf)
{
	GetDlgItemText(IDC_NAMEEDIT, *NameBuf);

	return 0;
}

int DataInput::GetStid(CString* StidBuf)
{
	GetDlgItemText(IDC_STIDEDIT, *StidBuf);

	return 0;
}

int  DataInput::GetKorScore()
{
	return GetDlgItemInt(IDC_KOREDIT);
}


int  DataInput::GetEngScore()
{
	return GetDlgItemInt(IDC_ENGEDIT);;
}


int  DataInput::GetMatScore()
{
	return GetDlgItemInt(IDC_MATEDIT);;
}

void DataInput::SetMode(int mode)    //수정, 추가모드 결정하는 메서드. 수정은 0, 추가는 1
{
	if (mode == 0)
	{
		m_NameEditInit = "";
		m_StidEditInit = "";
		m_KorEditInit = "";
		m_EngEditInit = "";
		m_MatEditInit = "";
	}

	m_Mode = mode;
}

int DataInput::SetName(CString StrName)
{
//	UpdateData(TRUE);
//	SetDlgItemText(IDC_NAMEEDIT, StrName);
//	UpdateData(FALSE);

	m_NameEditInit = StrName;

	return 0;
}

int DataInput::SetStid(CString StrStid)
{
//	SetDlgItemText(IDC_STIDEDIT, StrStid);
	m_StidEditInit = StrStid;
	return 0;
}

int DataInput::SetKorScore(CString StrKorScore)
{
//	SetDlgItemText(IDC_KOREDIT, StrKorScore);
	m_KorEditInit = StrKorScore;
	return 0;
}

int DataInput::SetEngScore(CString StrEngScore)
{
//	SetDlgItemText(IDC_ENGEDIT, StrEngScore);
	m_EngEditInit = StrEngScore;
	return 0;
}

int DataInput::SetMatScore(CString StrMatScore)
{
//	SetDlgItemText(IDC_MATEDIT, StrMatScore);
	m_MatEditInit = StrMatScore;
	return 0;
}

int DataInput::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}

BOOL DataInput::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgItemText(IDC_NAMEEDIT, m_NameEditInit);
	SetDlgItemText(IDC_STIDEDIT, m_StidEditInit);
	SetDlgItemText(IDC_KOREDIT, m_KorEditInit);
	SetDlgItemText(IDC_ENGEDIT, m_EngEditInit);
	SetDlgItemText(IDC_MATEDIT, m_MatEditInit);
	return TRUE;
}


BOOL DataInput::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}


