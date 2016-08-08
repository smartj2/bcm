// BISSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "BISSetting.h"
#include "afxdialogex.h"


// CBISSetting �Ի���
extern CBarcodeManagementApp theApp;

IMPLEMENT_DYNAMIC(CBISSetting, CDialogEx)

CBISSetting::CBISSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBISSetting::IDD, pParent)
	, m_ATLLen(_T(""))
	, m_Material(_T(""))
	, m_MI(_T(""))
	, m_Model(_T(""))
	, m_Qty(_T(""))
	, m_Tray(_T(""))
	, m_Supplier(_T(""))

{

}

CBISSetting::~CBISSetting()
{
}

void CBISSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BIS_LIST, m_BISList);
	DDX_Text(pDX, IDC_ATLLEN_EDIT, m_ATLLen);
	DDX_Text(pDX, IDC_MATERIAL_EDIT, m_Material);
	DDX_Text(pDX, IDC_MI_EDIT, m_MI);
	DDX_Text(pDX, IDC_MODEL_EDIT, m_Model);
	DDX_Text(pDX, IDC_QTY_EDIT, m_Qty);
	DDX_Text(pDX, IDC_TRAY_EDIT, m_Tray);
	DDX_Text(pDX, IDC_SUPPLIER_EDIT, m_Supplier);
}


BEGIN_MESSAGE_MAP(CBISSetting, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CBISSetting::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_MOD_BUTTON, &CBISSetting::OnBnClickedModButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CBISSetting::OnBnClickedExitButton)
	ON_NOTIFY(NM_DBLCLK, IDC_BIS_LIST, &CBISSetting::OnNMDblclkBisList)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CBISSetting::OnBnClickedDeleteButton)
END_MESSAGE_MAP()


// CBISSetting ��Ϣ�������

BOOL CBISSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_BISList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_BISList.InsertColumn(0,"��Ӧ��",LVCFMT_CENTER,50,0);
	m_BISList.InsertColumn(1,"����ͺ�",LVCFMT_CENTER,120,1);
	m_BISList.InsertColumn(2,"MI",LVCFMT_CENTER,60,2);
	m_BISList.InsertColumn(3,"�볤��",LVCFMT_CENTER,60,3);
	m_BISList.InsertColumn(4,"����",LVCFMT_CENTER,60,4);
	m_BISList.InsertColumn(5,"������",LVCFMT_CENTER,60,5);
	m_BISList.InsertColumn(6,"����",LVCFMT_CENTER,60,6);

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
		m_BISList.SetItemText(i,5,(char*)(_bstr_t)m_pRs->GetCollect("TraySize"));
		m_BISList.SetItemText(i,6,(char*)(_bstr_t)m_pRs->GetCollect("Material"));
		i++;
		m_pRs->MoveNext();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CBISSetting::OnBnClickedAddButton()
{
	UpdateData(true);
	if (m_Supplier.IsEmpty() || m_Model.IsEmpty() || m_MI.IsEmpty() 
		|| m_ATLLen.IsEmpty() || m_Qty.IsEmpty() || m_Material.IsEmpty())
	{
		AfxMessageBox("��д���ݲ���Ϊ�գ�");
		return;
	}

	CString sql = "insert into bBISInfo(Supplier,ProductModel,ProductMI, \
		BarcodeLen,Quantity,Material,TraySize) values('"+m_Supplier+"','"+m_Model+"', \
		'"+m_MI+"','"+m_ATLLen+"','"+m_Qty+"','"+m_Material+"','"+m_Tray+"')";

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
		m_BISList.SetItemText(i,5,(char*)(_bstr_t)m_pRs->GetCollect("TraySize"));
		m_BISList.SetItemText(i,6,(char*)(_bstr_t)m_pRs->GetCollect("Material"));
		i++;
		m_pRs->MoveNext();
	}

	m_Supplier = "";
	m_Model = "";
	m_MI = "";
	m_ATLLen = "";
	m_Qty = "";
	m_Material = "";

	UpdateData(false);
}


void CBISSetting::OnBnClickedModButton()
{
	UpdateData(true);

	if (m_Supplier.IsEmpty() || m_Model.IsEmpty() || m_MI.IsEmpty() 
		|| m_ATLLen.IsEmpty() || m_Qty.IsEmpty() || m_Material.IsEmpty())
	{
		AfxMessageBox("��д���ݲ���Ϊ�գ�");
		return;
	}

	CString sql = "update bBISInfo set Supplier='"+m_Supplier+"', ProductModel='"+m_Model+"', \
		BarcodeLen='"+m_ATLLen+"', Quantity='"+m_Qty+"', Material='"+m_Material+"', \
		TraySize='"+m_Tray+"' where ProductModel='"+m_Model+"'";

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
		m_BISList.SetItemText(i,5,(char*)(_bstr_t)m_pRs->GetCollect("TraySize"));
		m_BISList.SetItemText(i,6,(char*)(_bstr_t)m_pRs->GetCollect("Material"));
		i++;
		m_pRs->MoveNext();
	}

	m_Supplier = "";
	m_Model = "";
	m_MI = "";
	m_ATLLen = "";
	m_Qty = "";
	m_Tray = "";
	m_Material = "";

	UpdateData(false);
}


void CBISSetting::OnBnClickedDeleteButton()
{
	UpdateData(true);

	CString sql = "delete from bBISInfo where ProductModel='"+m_Model+"'";
	
	try
	{
		theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	} catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

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
		m_BISList.SetItemText(i,5,(char*)(_bstr_t)m_pRs->GetCollect("TraySize"));
		m_BISList.SetItemText(i,6,(char*)(_bstr_t)m_pRs->GetCollect("Material"));
		i++;
		m_pRs->MoveNext();
	}
	UpdateData(false);
}


void CBISSetting::OnBnClickedExitButton()
{
	CDialogEx::OnCancel();
}


void CBISSetting::OnNMDblclkBisList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	int i = m_BISList.GetSelectionMark();

	m_Supplier = m_BISList.GetItemText(i,0);
	m_Model = m_BISList.GetItemText(i,1);
	m_MI = m_BISList.GetItemText(i,2);
	m_ATLLen = m_BISList.GetItemText(i,3);
	m_Qty = m_BISList.GetItemText(i,4);
	m_Tray = m_BISList.GetItemText(i,5);
	m_Material = m_BISList.GetItemText(i,6);

	UpdateData(false);

	*pResult = 0;
}

