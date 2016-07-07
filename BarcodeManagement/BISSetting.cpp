// BISSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "BISSetting.h"
#include "afxdialogex.h"


// CBISSetting �Ի���

IMPLEMENT_DYNAMIC(CBISSetting, CDialogEx)

CBISSetting::CBISSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBISSetting::IDD, pParent)
	, m_ATLLen(_T(""))
	, m_Material(_T(""))
	, m_MI(_T(""))
	, m_Model(_T(""))
	, m_Qty(_T(""))
	, m_Supplier(_T(""))
{

}

CBISSetting::~CBISSetting()
{
}

void CBISSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ATLLEN_EDIT, m_ATLLen);
	DDX_Text(pDX, IDC_MATERIAL_EDIT, m_Material);
	DDX_Text(pDX, IDC_MI_EDIT, m_MI);
	DDX_Text(pDX, IDC_MODEL_EDIT, m_Model);
	DDX_Text(pDX, IDC_QTY_EDIT, m_Qty);
	DDX_Text(pDX, IDC_SUPPLIER_EDIT, m_Supplier);
	DDX_Control(pDX, IDC_BIS_LIST, m_BISList);
}


BEGIN_MESSAGE_MAP(CBISSetting, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CBISSetting::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_MOD_BUTTON, &CBISSetting::OnBnClickedModButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CBISSetting::OnBnClickedExitButton)
END_MESSAGE_MAP()


// CBISSetting ��Ϣ�������


BOOL CBISSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BISList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_BISList.InsertColumn(0,"��Ӧ��",LVCFMT_LEFT,120,0);
	m_BISList.InsertColumn(1,"�ͺ�",LVCFMT_LEFT,50,1);
	m_BISList.InsertColumn(2,"MI",LVCFMT_LEFT,50,2);
	m_BISList.InsertColumn(3,"�볤��",LVCFMT_LEFT,80,3);
	m_BISList.InsertColumn(4,"����",LVCFMT_LEFT,80,4);
	m_BISList.InsertColumn(5,"����",LVCFMT_LEFT,50,5);

	CString sql = "select * from bBISInfo";
	m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	int i = 0;
	while(!m_pRs->adoEOF)
	{
		m_BISList.InsertItem(i,"");
		m_BISList.SetItemText(i,0,(char*)(_bstr_t)m_pRs->GetCollect("Supplier"));
		m_BISList.SetItemText(i,1,(char*)(_bstr_t)m_pRs->GetCollect("ProductModel"));
		m_BISList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("ProductMI"));
		m_BISList.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("BarcodeLen"));
		m_BISList.SetItemText(i,4,(char*)(_bstr_t)m_pRs->GetCollect("Quantity"));
		m_BISList.SetItemText(i,5,(char*)(_bstr_t)m_pRs->GetCollect("Material"));
		i++;
		m_pRs->MoveNext();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CBISSetting::OnBnClickedAddButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_Supplier.IsEmpty() || m_Model.IsEmpty() || m_MI.IsEmpty() 
		|| m_ATLLen.IsEmpty() || m_Qty.IsEmpty() || m_Material.IsEmpty())
	{
		AfxMessageBox("��д���ݲ���Ϊ�գ�");
		return;
	}

	CString sql = "insert into bBISInfo(Supplier,ProductModel,ProductMI,\
		BarcodeLen,Quantity,Material) values('"+m_Supplier+"','"+m_Model+"',\
		'"+m_MI+"','"+m_ATLLen+"','"+m_Qty+"','"+m_Material+"')";

	theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	m_BISList.DeleteAllItems();

	m_pRs = theApp.m_pCon->Execute((_bstr_t)("select * from bBISInfo"),NULL,adCmdText);
	int i = 0;
	while(!m_pRs->adoEOF)
	{
		m_BISList.InsertItem(i,"");
		m_BISList.SetItemText(i,0,(char*)(_bstr_t)m_pRs->GetCollect("Supplier"));
		m_BISList.SetItemText(i,1,(char*)(_bstr_t)m_pRs->GetCollect("ProductModel"));
		m_BISList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("ProductMI"));
		m_BISList.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("BarcodeLen"));
		m_BISList.SetItemText(i,4,(char*)(_bstr_t)m_pRs->GetCollect("Quantity"));
		m_BISList.SetItemText(i,5,(char*)(_bstr_t)m_pRs->GetCollect("Material"));
		i++;
		m_pRs->MoveNext();
	}

	m_Supplier = "";
	m_Model = "";
	m_MI = "";
	m_ATLLen = "";
	m_Qty = "";
	m_Material = "";

	UpdateData(FALSE);
}


void CBISSetting::OnBnClickedModButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CBISSetting::OnBnClickedExitButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
