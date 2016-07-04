// SubConPack.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SubConPack.h"
#include "afxdialogex.h"


// CSubConPack �Ի���
extern CBarcodeManagementApp theApp;

IMPLEMENT_DYNAMIC(CSubConPack, CDialogEx)

CSubConPack::CSubConPack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSubConPack::IDD, pParent)
	, m_MarkBox(_T(""))
	, m_Barcode(_T(""))
{

}

CSubConPack::~CSubConPack()
{
}

void CSubConPack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PACK_EDIT, m_MarkBox);
	DDX_Text(pDX, IDC_BARCODE_EDIT, m_Barcode);
	DDX_Control(pDX, IDC_ATL_COMBO, m_ATL_Barcode);
	DDX_Control(pDX, IDC_MI_COMBO, m_MI);
	DDX_Control(pDX, IDC_PCS_COMBO, m_Piece);
	DDX_Control(pDX, IDC_QTY_COMBO, m_Qty);
	DDX_Control(pDX, IDC_BCM_LIST, m_Gird);
}


BEGIN_MESSAGE_MAP(CSubConPack, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CSubConPack::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_PACK_BUTTON, &CSubConPack::OnBnClickedPackButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CSubConPack::OnBnClickedExitButton)
	ON_EN_CHANGE(IDC_BARCODE_EDIT, &CSubConPack::OnEnChangeBarcodeEdit)
END_MESSAGE_MAP()


// CSubConPack ��Ϣ�������


void CSubConPack::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CSubConPack::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_Gird.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	
	// ���ñ�ͷ
	m_Gird.InsertColumn(0, "���", LVCFMT_CENTER, 120, 0);
	m_Gird.InsertColumn(0, "��Ʒ����", LVCFMT_CENTER, 150, 1);
	m_Gird.InsertColumn(0, "�������", LVCFMT_CENTER, 150, 2);
	m_Gird.InsertColumn(0, "��о����", LVCFMT_CENTER, 150, 3);
	m_Gird.InsertColumn(0, "����Ա", LVCFMT_CENTER, 100, 4);

	AddToGird();

	m_ATL_Barcode.SetCurSel(0);
	m_MI.SetCurSel(0);
	m_Piece.SetCurSel(0);
	m_Qty.SetCurSel(0);

	GetDlgItem(IDC_PACK_EDIT)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CSubConPack::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSubConPack::AddToGird()
{
	CString sql = "select * from BCM_Product_Info";
	m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	int i = 0;

	while(!m_pRs->adEOF)
	{
		m_Gird.InsertItem(i,"");
		m_Gird.SetItemText(i,0,(char*)(_bstr_t)m_pRs->GetCollect("BCM_Mark_Box"));
		m_Gird.SetItemText(i,1,(char*)(_bstr_t)m_pRs->GetCollect("BCM_Product_No"));
		m_Gird.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("BCM_MY_Barcode"));
		m_Gird.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("BCM_ATL_Barcode"));
		m_Gird.SetItemText(i,4,(char*)(_bstr_t)m_pRs->GetCollect("BCM_Operator"));
		i++;
		m_pRs->MoveNext();
	}

}

void CSubConPack::OnBnClickedPackButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CSubConPack::OnBnClickedExitButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}



void CSubConPack::OnEnChangeBarcodeEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (!m_Barcode.IsEmpty())
	{
		// TODO: ����List
		m_Barcode = "";
		UpdateData(FALSE);
		GetDlgItem(IDC_BARCODE_EDIT)->SetFocus();
	}
}
