// CartonQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "CartonQuery.h"
#include "afxdialogex.h"


// CCartonQuery 对话框

IMPLEMENT_DYNAMIC(CCartonQuery, CDialogEx)

CCartonQuery::CCartonQuery(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCartonQuery::IDD, pParent)
	, m_Query(_T(""))
{

}

CCartonQuery::~CCartonQuery()
{
}

void CCartonQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_QUERY_EDIT, m_Query);
	DDX_Control(pDX, IDC_RES_LIST, m_ResultList);
}


BEGIN_MESSAGE_MAP(CCartonQuery, CDialogEx)
	ON_BN_CLICKED(IDC_QUERY_BUTTON, &CCartonQuery::OnBnClickedQueryButton)
END_MESSAGE_MAP()


// CCartonQuery 消息处理程序


void CCartonQuery::OnBnClickedQueryButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_ResultList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_ResultList.InsertColumn(0,"外箱条码",LVCFMT_LEFT,120,0);
	m_ResultList.InsertColumn(1,"电芯条码",LVCFMT_LEFT,120,1);
	m_ResultList.InsertColumn(2,"电池条码",LVCFMT_LEFT,120,2);
	m_ResultList.InsertColumn(3,"扫描时间",LVCFMT_LEFT,120,3);


	CString sql = "select * from bBarcode where MarkBox='+m_Query+'";
	m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	int i = 0;
	while(!m_pRs->adoEOF)
	{
		m_ResultList.InsertItem(i,"");
		m_ResultList.SetItemText(i,0,(char*)(_bstr_t)m_pRs->GetCollect("MarkBox"));
		m_ResultList.SetItemText(i,1,(char*)(_bstr_t)m_pRs->GetCollect("ATLBarcode"));
		m_ResultList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("MYBarcode"));
		m_ResultList.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("ScanTime"));
		i++;
		m_pRs->MoveNext();
	}
}
