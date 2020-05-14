
// CLabMFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CLabMFC.h"
#include "CLabMFCDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCLabMFCDlg* g_CLabMFCDlg;

static int CALLBACK CompareFunc(LPARAM IParam1, LPARAM IParam2, LPARAM IParam)
{
	BOOL Ascending = (BOOL)IParam;
	LPCTSTR s1 = (LPCTSTR)(DWORD)IParam1;
	LPCTSTR s2 = (LPCTSTR)(DWORD)IParam2;
	if (Ascending)
		return _tcscmp(s1, s2);
	else
		return -(_tcscmp(s1, s2));

	return 0;
}


int DataUpdate()    //실제 데이터 입력 받기 및 변환, 출력.
{
	int rtn = g_CLabMFCDlg->DataUpdate();
	return 0;
}


int DataModify()
{
	int rtn = g_CLabMFCDlg->DataModify();
	return 0;
}
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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
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


// CCLabMFCDlg 대화 상자



CCLabMFCDlg::CCLabMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLABMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCLabMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_DATALIST, m_DataList);
	DDX_Control(pDX, IDC_SEARCHMENU, m_SearchMenu);
	DDX_Control(pDX, IDC_SEARCHEDIT, m_SearchEdit);
}

BEGIN_MESSAGE_MAP(CCLabMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DATAINPUT_B, &CCLabMFCDlg::OnBnClickedDatainputB)
	ON_BN_CLICKED(IDC_DELETE, &CCLabMFCDlg::OnBnClickedDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DATALIST, &CCLabMFCDlg::OnLvnItemchangedDatalist)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_DATALIST, &CCLabMFCDlg::OnColumnclickDatalist)
	ON_BN_CLICKED(IDC_FIX, &CCLabMFCDlg::OnBnClickedFix)
	ON_BN_CLICKED(IDC_SEARCHB, &CCLabMFCDlg::OnBnClickedSearchb)
	ON_BN_CLICKED(IDC_FILESAVE, &CCLabMFCDlg::OnBnClickedFilesave)
	ON_BN_CLICKED(IDC_TXTB, &CCLabMFCDlg::OnBnClickedTxtb)
	ON_BN_CLICKED(IDC_EXCELB, &CCLabMFCDlg::OnBnClickedExcelb)
	ON_BN_CLICKED(IDC_HTMLB, &CCLabMFCDlg::OnBnClickedHtmlb)
END_MESSAGE_MAP()


// CCLabMFCDlg 메시지 처리기

BOOL CCLabMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
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

	g_CLabMFCDlg = this;
	m_DataList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); //GRID형태로 줄출력 및 선택기능 활성.
	m_DataList.InsertColumn(0, _T("석차"), LVCFMT_CENTER, 50);  //List Cont에서 Column넣는 방법.
	m_DataList.InsertColumn(1, _T("이름"), LVCFMT_CENTER, 50);
	m_DataList.InsertColumn(2, _T("학번"), LVCFMT_CENTER, 100);
	m_DataList.InsertColumn(3, _T("국어"), LVCFMT_CENTER, 50);
	m_DataList.InsertColumn(4, _T("영어"), LVCFMT_CENTER, 50);
	m_DataList.InsertColumn(5, _T("수학"), LVCFMT_CENTER, 50);
	m_DataList.InsertColumn(6, _T("합계"), LVCFMT_CENTER, 50);
	m_DataList.InsertColumn(7, _T("평균"), LVCFMT_CENTER, 50);
	m_DataList.InsertColumn(8, _T("등급"), LVCFMT_CENTER, 50);

	m_SearchMenu.InsertString(0, TEXT("학번"));
	m_SearchMenu.InsertString(1, TEXT("이름"));
	m_SearchMenu.InsertString(2, TEXT("석차"));
	m_SearchMenu.InsertString(3, TEXT("등급"));


	m_ProfileFont.CreateFont(30, 8, 0, 0, 800, 1, 0, 0, 0, OUT_DEFAULT_PRECIS,
			0, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("굴림"));
	GetDlgItem(IDC_PROFILE1)->SetFont(&m_ProfileFont);
	GetDlgItem(IDC_PROFILE2)->SetFont(&m_ProfileFont);


	//프로그램 실행시 데이터 업로드
	char fname[128];

	strcpy(fname, "성적데이터.txt");
	// 성적파일 쓰기 모드로 오픈
	if ((m_SaveFile = fopen(fname, "r")) != NULL)
	{
		int rtn;
		int RowNum = 0;     //행 입력 순서대로
		int Total = 0;      //합계
		int Average = 0;    //평균
		char GradeNum = 0;  //등급
		char Stid[256];
		char Name[256];
		int KorScore = 0;   //DataInput으로부터 입력받은 국어점수
		int EngScore = 0;   //DataInput으로부터 입력받은 영어점수
		int MatScore = 0;   //DataInput으로부터 입력받은 수학점수

		CString StrName;
		CString StrStid;
		CString StrKorScore;   //숫자를 따로 입력받는 함수가 없어서 문자열 형태로 저장.
		CString StrEngScore;   //아래 동일
		CString StrMatScore;
		CString StrTotal;
		CString StrAverage;
		CString StrGradeNum;
		CString StrRank;

		while (!feof(m_SaveFile))
		{
			fscanf(m_SaveFile, "%s %s %d %d %d"
				, Name, Stid, &KorScore, &EngScore, &MatScore);
			if (feof(m_SaveFile)) { break; }

			Total = KorScore + EngScore + MatScore;   //계산
			Average = Total / 3;
			GradeNum = Grade(Average);

			StrName = Name;
			StrStid = Stid;
			StrKorScore.Format(_T("%d"), KorScore);   //점수들은 다 int형이라 이름, 학번처럼 못함. CString으로 다시 저장
			StrEngScore.Format(_T("%d"), EngScore);
			StrMatScore.Format(_T("%d"), MatScore);
			StrTotal.Format(_T("%d"), Total);
			StrAverage.Format(_T("%d"), Average);
			StrGradeNum.Format(_T("%c"), GradeNum);   //등급은 알파뱃이라 %c사용

			int rank = GetRank(Total);
			StrRank.Format(_T("%d"), rank);

			RowNum = m_DataList.GetItemCount();

			m_DataList.InsertItem(RowNum, StrRank);   //행변환. 및 석차(?)

			m_DataList.SetItem(RowNum, 1, LVIF_TEXT, StrName, NULL, NULL, NULL, NULL);  //CString값 출력.
			m_DataList.SetItem(RowNum, 2, LVIF_TEXT, StrStid, NULL, NULL, NULL, NULL);

			m_DataList.SetItem(RowNum, 3, LVIF_TEXT, StrKorScore, NULL, NULL, NULL, NULL);
			m_DataList.SetItem(RowNum, 4, LVIF_TEXT, StrEngScore, NULL, NULL, NULL, NULL);
			m_DataList.SetItem(RowNum, 5, LVIF_TEXT, StrMatScore, NULL, NULL, NULL, NULL);
			m_DataList.SetItem(RowNum, 6, LVIF_TEXT, StrTotal, NULL, NULL, NULL, NULL);
			m_DataList.SetItem(RowNum, 7, LVIF_TEXT, StrAverage, NULL, NULL, NULL, NULL);
			m_DataList.SetItem(RowNum, 8, LVIF_TEXT, StrGradeNum, NULL, NULL, NULL, NULL);

			rtn = SetRank();
		}

		fclose(m_SaveFile);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCLabMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCLabMFCDlg::OnPaint()
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
HCURSOR CCLabMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCLabMFCDlg::OnBnClickedDatainputB()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_DataInput.SetMode(0);  //추가모드

	m_DataInput.DoModal();
}



char CCLabMFCDlg::Grade(int X) //등급 변환함수
{
	char grade;

	if (X >= 90) grade = 'A';
	else 	if (X >= 80) grade = 'B';
	else 	if (X >= 70) grade = 'C';
	else 	if (X >= 60) grade = 'D';
	else 	if (X <= 59) grade = 'F';
	return grade;
}

int CCLabMFCDlg::GetRank(int X)  //데이터가 추가된다면 몇등일지 판단.
{
	int cnt = m_DataList.GetItemCount();
	int cntp = 1;

	for (int i = 0; i < cnt; i++)
	{
		CString StrTotal = m_DataList.GetItemText(i, 6);
		int total = _ttoi(StrTotal);
		if (X < total)
			cntp++;
	}
	return cntp;
}

int CCLabMFCDlg::SetRank()  //다시 등수 매기기
{
	int cnt = m_DataList.GetItemCount();


	for (int i = 0; i < cnt; i++)
	{
		int cntP = 1;
		int total1 = 0;
		CString StrTotal = m_DataList.GetItemText(i, 7);
		total1 = _ttoi(StrTotal);

		for (int j = 0; j < cnt; j++)
		{
			int total2 = 0;
			CString StrTotal2 = m_DataList.GetItemText(j, 7);
			total2 = _ttoi(StrTotal2);

			if (total1 < total2)
				cntP++;
		}
		CString StrNewRank;
		StrNewRank.Format(_T("%d"), cntP);
		m_DataList.SetItem(i, 0, LVIF_TEXT, StrNewRank, NULL, NULL, NULL, NULL);
	}

	return 0;
}

int CCLabMFCDlg::DataModify()
{
	int rtn;
	int count = 0;
	int RowNum = 0;     //행 입력 순서대로
	int Total = 0;      //합계
	int Average = 0;    //평균
	char GradeNum = 0;  //등급
	int KorScore = 0;   //DataInput으로부터 입력받은 국어점수
	int EngScore = 0;   //DataInput으로부터 입력받은 영어점수
	int MatScore = 0;   //DataInput으로부터 입력받은 수학점수

	CString StrName;
	CString StrStid;
	CString StrKorScore;   //숫자를 따로 입력받는 함수가 없어서 문자열 형태로 저장.
	CString StrEngScore;   //아래 동일
	CString StrMatScore;
	CString StrTotal;
	CString StrAverage;
	CString StrGradeNum;
	CString StrRank;
		
	count = m_DataList.GetItemCount();
	for (int i = count; i >= 0; i--)
	{
		if (m_DataList.GetItemState(i, LVIS_SELECTED) != 0) //선택된것 확인
		{
			RowNum = i; //선택된 행
		}
	}

	rtn = m_DataInput.GetName(&StrName);    //rtn인 이유는 함수가 0으로 반환하기 때문.(포인터사용)
	rtn = m_DataInput.GetStid(&StrStid);    //Get함수들로 DataInput에서 입력받은 값을 문자열형태로 변환.
	KorScore = m_DataInput.GetKorScore();   //Get함수들로 DataInput에서 입력받은 값 저장.
	EngScore = m_DataInput.GetEngScore();   //아래 동일
	MatScore = m_DataInput.GetMatScore();

	Total = KorScore + EngScore + MatScore;   //계산
	Average = Total / 3;
	GradeNum = Grade(Average);

	StrKorScore.Format(_T("%d"), KorScore);   //점수들은 다 int형이라 이름, 학번처럼 못함. CString으로 다시 저장
	StrEngScore.Format(_T("%d"), EngScore);
	StrMatScore.Format(_T("%d"), MatScore);
	StrTotal.Format(_T("%d"), Total);
	StrAverage.Format(_T("%d"), Average);
	StrGradeNum.Format(_T("%c"), GradeNum);   //등급은 알파뱃이라 %c사용

	int rank = GetRank(Total);
	StrRank.Format(_T("%d"), rank);

	m_DataList.SetItem(RowNum, 0, LVIF_TEXT, StrRank, NULL, NULL, NULL, NULL);   

	m_DataList.SetItem(RowNum, 1, LVIF_TEXT, StrName, NULL, NULL, NULL, NULL);  //CString값 출력.
	m_DataList.SetItem(RowNum, 2, LVIF_TEXT, StrStid, NULL, NULL, NULL, NULL);

	m_DataList.SetItem(RowNum, 3, LVIF_TEXT, StrKorScore, NULL, NULL, NULL, NULL);
	m_DataList.SetItem(RowNum, 4, LVIF_TEXT, StrEngScore, NULL, NULL, NULL, NULL);
	m_DataList.SetItem(RowNum, 5, LVIF_TEXT, StrMatScore, NULL, NULL, NULL, NULL);
	m_DataList.SetItem(RowNum, 6, LVIF_TEXT, StrTotal, NULL, NULL, NULL, NULL);
	m_DataList.SetItem(RowNum, 7, LVIF_TEXT, StrAverage, NULL, NULL, NULL, NULL);
	m_DataList.SetItem(RowNum, 8, LVIF_TEXT, StrGradeNum, NULL, NULL, NULL, NULL);

	rtn = SetRank();
	return 0;
}


int CCLabMFCDlg::DataUpdate()
{
	int rtn;
	int RowNum = 0;     //행 입력 순서대로
	int Total = 0;      //합계
	int Average = 0;    //평균
	char GradeNum = 0;  //등급
	int KorScore = 0;   //DataInput으로부터 입력받은 국어점수
	int EngScore = 0;   //DataInput으로부터 입력받은 영어점수
	int MatScore = 0;   //DataInput으로부터 입력받은 수학점수

	CString StrName;
	CString StrStid;
	CString StrKorScore;   //숫자를 따로 입력받는 함수가 없어서 문자열 형태로 저장.
	CString StrEngScore;   //아래 동일
	CString StrMatScore;
	CString StrTotal;
	CString StrAverage;
	CString StrGradeNum;
	CString StrRank;

	RowNum = m_DataList.GetItemCount();

	rtn = m_DataInput.GetName(&StrName);    //rtn인 이유는 함수가 0으로 반환하기 때문.(포인터사용)
	rtn = m_DataInput.GetStid(&StrStid);    //Get함수들로 DataInput에서 입력받은 값을 문자열형태로 변환.
	KorScore = m_DataInput.GetKorScore();   //Get함수들로 DataInput에서 입력받은 값 저장.
	EngScore = m_DataInput.GetEngScore();   //아래 동일
	MatScore = m_DataInput.GetMatScore();

	Total = KorScore + EngScore + MatScore;   //계산
	Average = Total / 3;
	GradeNum = Grade(Average);

	StrKorScore.Format(_T("%d"), KorScore);   //점수들은 다 int형이라 이름, 학번처럼 못함. CString으로 다시 저장
	StrEngScore.Format(_T("%d"), EngScore);
	StrMatScore.Format(_T("%d"), MatScore);
	StrTotal.Format(_T("%d"), Total);
	StrAverage.Format(_T("%d"), Average);
	StrGradeNum.Format(_T("%c"), GradeNum);   //등급은 알파뱃이라 %c사용

	int rank = GetRank(Total);
	StrRank.Format(_T("%d"), rank);

	m_DataList.InsertItem(RowNum, StrRank);   //행변환. 및 석차(?)

	m_DataList.SetItem(RowNum, 1, LVIF_TEXT, StrName, NULL, NULL, NULL, NULL);  //CString값 출력.
	m_DataList.SetItem(RowNum, 2, LVIF_TEXT, StrStid, NULL, NULL, NULL, NULL);

	m_DataList.SetItem(RowNum, 3, LVIF_TEXT, StrKorScore, NULL, NULL, NULL, NULL);
	m_DataList.SetItem(RowNum, 4, LVIF_TEXT, StrEngScore, NULL, NULL, NULL, NULL);
	m_DataList.SetItem(RowNum, 5, LVIF_TEXT, StrMatScore, NULL, NULL, NULL, NULL);
	m_DataList.SetItem(RowNum, 6, LVIF_TEXT, StrTotal, NULL, NULL, NULL, NULL);
	m_DataList.SetItem(RowNum, 7, LVIF_TEXT, StrAverage, NULL, NULL, NULL, NULL);
	m_DataList.SetItem(RowNum, 8, LVIF_TEXT, StrGradeNum, NULL, NULL, NULL, NULL);

	rtn = SetRank();
	return 0;
}


void CCLabMFCDlg::OnBnClickedDelete()
{
	int count = m_DataList.GetItemCount();//DataList에 적힌 값들 갯수

	for (int i = count; i >= 0; i--)
	{
		if (m_DataList.GetItemState(i, LVIS_SELECTED) != 0) //선택된것 확인
		{
			m_DataList.DeleteItem(i); //삭제
		}
	}
	int rtn = SetRank(); //삭제시 순위 다시 매김.
}


void CCLabMFCDlg::OnLvnItemchangedDatalist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CCLabMFCDlg::OnColumnclickDatalist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int column = pNMLV->iSubItem;
	if (column == m_nSortedColumn)
	{
		m_bAscending = !m_bAscending;
	}
	else
	{
		m_bAscending = TRUE;
	}

	m_nSortedColumn = column;
	int cnt = m_DataList.GetItemCount();
	CString* str = new CString[cnt];

	for (int i = 0; i < cnt; i++)
	{
		str[i] = m_DataList.GetItemText(i, column);
		m_DataList.SetItemData(i, (DWORD)(LPCTSTR)str[i]);
	}

	m_DataList.SortItems(CompareFunc, (LPARAM)m_bAscending);
	delete[]str;


	*pResult = 0;
}


void CCLabMFCDlg::OnBnClickedFix()
{
	m_DataInput.SetMode(1);  //수정모드

	int count = m_DataList.GetItemCount();//DataList에 적힌 값들 갯수
	CString StrName;
	CString StrStid;
	CString StrKorScore;
	CString StrEngScore;
	CString StrMatScore;

	for (int i = count; i >= 0; i--)
	{
		if (m_DataList.GetItemState(i, LVIS_SELECTED) != 0) //선택된것 확인
		{
			StrName = m_DataList.GetItemText(i, 1);
			StrStid = m_DataList.GetItemText(i, 2);
			StrKorScore = m_DataList.GetItemText(i, 3);
			StrEngScore = m_DataList.GetItemText(i, 4);
			StrMatScore = m_DataList.GetItemText(i, 5);
		}
	}
	m_DataInput.SetName(StrName);
	m_DataInput.SetStid(StrStid);
	m_DataInput.SetKorScore(StrKorScore);
	m_DataInput.SetEngScore(StrEngScore);
	m_DataInput.SetMatScore(StrMatScore);

	m_DataInput.DoModal();

	int rtn = SetRank();
}


void CCLabMFCDlg::OnBnClickedSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

#define STID 0
#define NAME 1
#define RANK 2
#define GRAD 3

void CCLabMFCDlg::OnBnClickedSearchb()//조회버튼 
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int column = 0;	//행
	int menuindex = m_SearchMenu.GetCurSel();	//선택확인
	switch (menuindex)
	{
	case STID: column = 2;	break;	//학번
	case NAME: column = 1;	break;	//이름
	case RANK: column = 0;	break;	//석차
	case GRAD: column = 8;	break;	//등급
	}

	m_DataList.SetItemState(-1, 0, LVIS_SELECTED | LVIS_FOCUSED);	//모든 선택된 상자 선택 해제

	for (int i = 0; i < m_DataList.GetItemCount(); i++)
	{

		CString targetword = m_DataList.GetItemText(i, column);
		CString searchword;
		m_SearchEdit.GetWindowText(searchword);

		if (targetword.Find(searchword) >= 0)	//같을 경우 0(cmp)
		{
			m_DataList.SetItemState(i, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);		//같은값 선택
			m_DataList.SetItemState(i, FALSE);	//화면에 출력
			m_DataList.SetFocus();
		}
	}
}


void CCLabMFCDlg::OnBnClickedFilesave()   //데이터 저장
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char fname[100];
	CString SaveName;
	CString SaveStid;
	CString SaveKorScore;
	CString SaveEngScore;
	CString SaveMatScore;

	//mbstowcs형을 만족하기위해선 wchar_t, const char*형이 필요.
	wchar_t SaveNameST[128];
	wchar_t SaveStidST[128];
	wchar_t SaveKorScoreST[128];
	wchar_t SaveEngScoreST[128];
	wchar_t SaveMatScoreST[128];

	strcpy(fname, "성적데이터.txt");
	// 성적파일 쓰기 모드로 오픈
	if ((m_SaveFile = fopen(fname, "w")) == NULL)
	{
		MessageBox( L"(WARNING) CAN NOT OPEN THE FILE.", L"ERROR", 0);
		return;
	}

	for (int i = 0; i < m_DataList.GetItemCount(); i++)
	{
		SaveName = m_DataList.GetItemText(i, 1);
		SaveStid = m_DataList.GetItemText(i, 2);
		SaveKorScore = m_DataList.GetItemText(i, 3);
		SaveEngScore = m_DataList.GetItemText(i, 4);
		SaveMatScore = m_DataList.GetItemText(i, 5);

		//const char*형 대신 선택한 방법.(??나도몰라)
		CT2A asciiName(SaveName);
		CT2A asciiStid(SaveStid);
		CT2A asciiKorScore(SaveKorScore);
		CT2A asciiEngScore(SaveEngScore);
		CT2A asciiMatScore(SaveMatScore);

		mbstowcs(SaveNameST, asciiName.m_psz, 128);
		mbstowcs(SaveStidST, asciiStid.m_psz, 128);
		mbstowcs(SaveKorScoreST, asciiKorScore.m_psz, 128);
		mbstowcs(SaveEngScoreST, asciiEngScore.m_psz, 128);
		mbstowcs(SaveMatScoreST, asciiMatScore.m_psz, 128);

		fprintf(m_SaveFile, "%S %S %S %S %S\n"
			, SaveNameST, SaveStidST, SaveKorScoreST
			, SaveEngScoreST, SaveMatScoreST);
			
	}
	MessageBox(L" SAVE COMPLETE ", L"FILE SAVE", 0);
	
	fclose(m_SaveFile);
}


void CCLabMFCDlg::OnBnClickedTxtb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char fname[256];
	char fnametxt[256];
	int total;
	int average;

	char SaveName[128];
	char SaveStid[128];
	int SaveKorScore;
	int SaveEngScore;
	int SaveMatScore;


	if (IDYES == AfxMessageBox(_T("저장 후 출력하시겠습니까?"), MB_YESNO))
	{
		//OK Action
		OnBnClickedFilesave();
	}
	else
	{
		//NO Action
	}

	// 성적데이터.txt 파일을 읽기 모드로 연다
	strcpy(fname, "성적데이터.txt");
	if ((m_SaveFile = fopen(fname, "r")) == NULL)
	{
		MessageBox(L"(WARNING) CAN NOT OPEN THE FILE.", L"ERROR", 0);
		return;
	}

	// 성적집계표-1.txt 파일을 쓰기 모드로 연다
	strcpy(fnametxt, "성적집계표.txt");
	if ((m_TxtFile = fopen(fnametxt, "w")) == NULL)
	{
		MessageBox(L"(WARNING) CAN NOT MAKE A FILE.", L"ERROR", 0);
		return;
	}

	// 성적집계표 출력
	fprintf(m_TxtFile, "\n\t 성적집계표.txt");
	fprintf(m_TxtFile, "\n ========= ====== ==== ==== ==== ==== ==== ====");
	fprintf(m_TxtFile, "\n 학     번 이  름 국어 영어 수학 합계 평균 등급");
	fprintf(m_TxtFile, "\n ========= ====== ==== ==== ==== ==== ==== ====");


	while (!feof(m_SaveFile)) {
		fscanf(m_SaveFile, "%s %s %d %d %d"
			, SaveStid, SaveName, &SaveKorScore, &SaveEngScore, &SaveMatScore);
		if (feof(m_SaveFile)) { break; }

		total = SaveKorScore + SaveEngScore + SaveMatScore;
		average = total / 3;

		fprintf(m_TxtFile, "\n %s %s %4d %4d %4d %5d %4d   %c"
			, SaveStid, SaveName, SaveKorScore
			, SaveEngScore, SaveMatScore, total, average, Grade(average));
	}
	fprintf(m_TxtFile, "\n ========= ====== ==== ==== ==== ==== ==== ====\n ");

	// 입/출력 파일 닫기	
	fclose(m_SaveFile);
	fclose(m_TxtFile);
	system("성적집계표.txt");
}


void CCLabMFCDlg::OnBnClickedExcelb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char fname[256];
	char fnameExcel[256];
	int total;
	int average;

	char SaveName[128];
	char SaveStid[128];
	int SaveKorScore;
	int SaveEngScore;
	int SaveMatScore;


	if (IDYES == AfxMessageBox(_T("저장 후 출력하시겠습니까?"), MB_YESNO))
	{
		//OK Action
		OnBnClickedFilesave();
	}
	else
	{
		//NO Action
	}


	// 입력 파일 열기----------------------------------------------------	
	strcpy(fname, "성적데이터.TXT");

	if ((m_SaveFile = fopen(fname, "r")) == NULL)
	{
		MessageBox(L"(WARNING) CAN NOT OPEN THE FILE.", L"ERROR", 0);
		return;
	}

	// 출력 파일 열기----------------------------------------------------	
	strcpy(fnameExcel, "성적집계표.CSV");
	if ((m_ExcelFile = fopen(fnameExcel, "w")) == NULL)
	{
		MessageBox(L"(WARNING) CAN NOT MAKE A FILE.", L"ERROR", 0);
		return;
	}

	// 성적집계표 (그대로, CSV) 출력----------------------------------------
	fprintf(m_ExcelFile, "유수봉의 성적표 만들기(CSV) \n");
	fprintf(m_ExcelFile, "==========,=====,=====,=====,=====,=====,=====,===== \n");
	fprintf(m_ExcelFile, "학번,이름,국어,영어,수학,합계,평균,등급 \n");
	fprintf(m_ExcelFile, "==========,=====,=====,=====,=====,=====,=====,===== \n");

	while (!feof(m_SaveFile)) {
		fscanf(m_SaveFile, "%s %s %d %d %d"
			, SaveStid, SaveName, &SaveKorScore, &SaveEngScore, &SaveMatScore);
		if (feof(m_SaveFile)) { break; }

		total = SaveKorScore + SaveEngScore + SaveMatScore;
		average = total / 3;

		fprintf(m_ExcelFile, "%s, %s, %d, %d, %d, %d, %d, %c\n"
			, SaveStid, SaveName, SaveKorScore
			, SaveEngScore, SaveMatScore, total, average, Grade(average));
	}
	fprintf(m_ExcelFile, "==========,=====,=====,=====,=====,=====,=====,===== \n");

	// 입출력 파일 닫기----------------------------------------------------
	fclose(m_SaveFile);
	fclose(m_ExcelFile);
	system("성적집계표.CSV");
}




void CCLabMFCDlg::OnBnClickedHtmlb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char fname[256];
	char fnameHTML[256];
	int total;
	int average;

	char SaveName[128];
	char SaveStid[128];
	int SaveKorScore;
	int SaveEngScore;
	int SaveMatScore;


	if (IDYES == AfxMessageBox(_T("저장 후 출력하시겠습니까?"), MB_YESNO))
	{
		//OK Action
		OnBnClickedFilesave();
	}
	else
	{
		//NO Action
	}


	// 입력 파일 열기
	strcpy(fname, "성적데이터.txt");

	if ((m_SaveFile = fopen(fname, "r")) == NULL)
	{
		MessageBox(L"(WARNING) CAN NOT OPEN THE FILE.", L"ERROR", 0);
		return;
	}

	// 출력 파일 열기	
	strcpy(fnameHTML, "성적집계표.HTML");
	if ((m_HTMLFile = fopen(fnameHTML, "w")) == NULL)
	{
		MessageBox(L"(WARNING) CAN NOT MAKE A FILE.", L"ERROR", 0);
		return;
	}

	// 성적집계표-1 (그대로, HTML) 출력----------------------------------------
	fprintf(m_HTMLFile, "<!DOCTYPE html><HTML><HEAD> \n");

	fprintf(m_HTMLFile, "<TITLE>오규태의 HTML 성적표</TITLE> \n");
	fprintf(m_HTMLFile, "<STYLE> \n");
	fprintf(m_HTMLFile, "table {border-collapse: collapse; text-align: center; width: 500px; } \n");
	fprintf(m_HTMLFile, "table tr:hover {background-color: lightgreen; height:40px;} \n");
	fprintf(m_HTMLFile, "</STYLE></HEAD><BODY> \n");
	fprintf(m_HTMLFile, "<DIV align=center><H2>오규태의 성적표 만들기(HTML)</H2></DIV> \n");
	fprintf(m_HTMLFile, "<TABLE border=1 align=center> \n");
	fprintf(m_HTMLFile, "<THEAD> \n");
	fprintf(m_HTMLFile, "<TR><TH>학번</TH><TH>이름</TH><TH>국어</TH><TH>영어</TH><TH>수학</TH><TH>합계</TH><TH>평균</TH><TH>등급</TH></TR> \n");
	fprintf(m_HTMLFile, "</THEAD><TBODY> \n");

	while (!feof(m_SaveFile)) 
	{
		fscanf(m_SaveFile, "%s %s %d %d %d"
			, SaveStid, SaveName, &SaveKorScore, &SaveEngScore, &SaveMatScore);
		if (feof(m_SaveFile)) { break; }
		total = SaveKorScore + SaveEngScore + SaveMatScore;
		average = total / 3;

		fprintf(m_HTMLFile, "<TR><TD>%s</TD><TD>%s</TD><TD>%d</TD><TD>%d</TD><TD>%d</TD><TD>%d</TD><TD>%d</TD><TD>%c</TD></TR> \n"
			, SaveStid, SaveName, SaveKorScore
			, SaveEngScore, SaveMatScore, total, average, Grade(average));
	}

	fprintf(m_HTMLFile, "</TBODY> \n");
	fprintf(m_HTMLFile, "</TABLE> \n");
	fprintf(m_HTMLFile, "</BODY> \n </HTML> \n");

	// 입/출력 파일 닫기----------------------------------------------------
	fclose(m_SaveFile);
	fclose(m_HTMLFile);
	system("성적집계표.HTML");
}


BOOL CAboutDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;


	return CDialogEx::PreTranslateMessage(pMsg);
}
