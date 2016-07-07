// SGMLine.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SGMLine.h"
#include "afxdialogex.h"


// CSGMLine �Ի���

IMPLEMENT_DYNAMIC(CSGMLine, CDialogEx)

CSGMLine::CSGMLine(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSGMLine::IDD, pParent)
	, m_SGMQA(_T(""))
	, m_SGMLine(_T(""))
	, m_SGMTray(_T(""))
{

}

CSGMLine::~CSGMLine()
{
}

void CSGMLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SGM_LIST, m_SGMList);
	DDX_Text(pDX, IDC_SGMQA_EDIT, m_SGMQA);
	DDX_Text(pDX, IDC_SGMLINE_EDIT, m_SGMLine);
	DDX_Text(pDX, IDC_SGMTRAY_EDIT, m_SGMTray);
}


BEGIN_MESSAGE_MAP(CSGMLine, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CSGMLine::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, &CSGMLine::OnBnClickedCancelButton)
END_MESSAGE_MAP()


// CSGMLine ��Ϣ�������


void CSGMLine::OnBnClickedAddButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_SGMQA.IsEmpty() || m_SGMLine.IsEmpty() || m_SGMTray.IsEmpty())
	{
		AfxMessageBox("��д���ݲ���Ϊ�գ�");
		return;
	}

	CString sql = "insert into bSGMInfo(SGMQA,SGMLine,\
		SGMTray) values('"+m_SGMQA+"','"+m_SGMLine+"','"+m_SGMTray+"')";

	theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	m_SGMList.DeleteAllItems();

	m_pRs = theApp.m_pCon->Execute((_bstr_t)("select * from bSGMInfo"),NULL,adCmdText);
	int i = 0;
	while(!m_pRs->adoEOF)
	{
		m_SGMList.InsertItem(i,"");
		m_SGMList.SetItemText(i,0,(char*)(_bstr_t)m_pRs->GetCollect("SGMQA"));
		m_SGMList.SetItemText(i,1,(char*)(_bstr_t)m_pRs->GetCollect("SGMLine"));
		m_SGMList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("SGMTray"));
		i++;
		m_pRs->MoveNext();
	}

	m_SGMQA = "";
	m_SGMLine = "";
	m_SGMTray = "";

	UpdateData(FALSE);
}


void CSGMLine::OnBnClickedCancelButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


BOOL CSGMLine::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_SGMList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_SGMList.InsertColumn(0,"Ʒ�ʼ�Ա",LVCFMT_LEFT,120,0);
	m_SGMList.InsertColumn(1,"������/��",LVCFMT_LEFT,50,1);
	m_SGMList.InsertColumn(2,"��������",LVCFMT_LEFT,50,2);

	CString sql = "select * from bSGMInfo";
	m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	int i = 0;
	while(!m_pRs->adoEOF)
	{
		m_SGMList.InsertItem(i,"");
		m_SGMList.SetItemText(i,0,(char*)(_bstr_t)m_pRs->GetCollect("SGMQA"));
		m_SGMList.SetItemText(i,1,(char*)(_bstr_t)m_pRs->GetCollect("SGMLine"));
		m_SGMList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("SGMTray"));
		i++;
		m_pRs->MoveNext();
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
