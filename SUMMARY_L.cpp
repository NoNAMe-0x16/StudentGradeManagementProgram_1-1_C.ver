#include "Summary_L.h"
#include "Summary_L.h"
// SUMMARY_L.cpp: 구현 파일
//

#include "pch.h"
#include "CLabMFC.h"
#include "SUMMARY_L.h"
#include "afxdialogex.h"


// SUMMARY_L 대화 상자

IMPLEMENT_DYNAMIC(SUMMARY_L, CDialogEx)

SUMMARY_L::SUMMARY_L(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SUMMARY_L, pParent)
{

}

SUMMARY_L::~SUMMARY_L()
{
}

void SUMMARY_L::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SUMMARY_L, CDialogEx)
END_MESSAGE_MAP()


// SUMMARY_L 메시지 처리기
BEGIN_MESSAGE_MAP(Summary_L, CDialogEx)
	ON_BN_CLICKED(IDC_TXT_N, &Summary_L::OnBnClickedTxtN)
END_MESSAGE_MAP()


void Summary_L::OnBnClickedTxtN()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
