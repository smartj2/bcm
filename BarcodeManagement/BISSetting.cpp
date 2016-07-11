// BISSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "BISSetting.h"
#include "afxdialogex.h"


// CBISSetting 对话框
extern CBarcodeManagementApp theApp;

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
	DDX_Control(pDX, IDC_BIS_LIST, m_BISList);
	DDX_Text(pDX, IDC_ATLLEN_EDIT, m_ATLLen);
	DDX_Text(pDX, IDC_MATERIAL_EDIT, m_Material);
	DDX_Text(pDX, IDC_MI_EDIT, m_MI);
	DDX_Text(pDX, IDC_MODEL_EDIT, m_Model);
	DDX_Text(pDX, IDC_QTY_EDIT, m_Qty);
	DDX_Text(pDX, IDC_SUPPLIER_EDIT, m_Supplier);
}


BEGIN_MESSAGE_MAP(CBISSetting, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CBISSetting::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_MOD_BUTTON, &CBISSetting::OnBnClickedModButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CBISSetting::OnBnClickedExitButton)
	ON_NOTIFY(NM_DBLCLK, IDC_BIS_LIST, &CBISSetting::OnNMDblclkBisList)
END_MESSAGE_MAP()


// CBISSetting 消息处理程序


BOOL CBISSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_BISList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_BISList.InsertColumn(0,"供应商",LVCFMT_CENTER,50,0);
	m_BISList.InsertColumn(1,"型号",LVCFMT_CENTER,120,1);
	m_BISList.InsertColumn(2,"MI",LVCFMT_CENTER,60,2);
	m_BISList.InsertColumn(3,"码长度",LVCFMT_CENTER,60,3);
	m_BISList.InsertColumn(4,"数量",LVCFMT_CENTER,60,4);
	m_BISList.InsertColumn(5,"物料",LVCFMT_CENTER,80,5);

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
	// 异常: OCX 属性页应返回 FALSE
}


void CBISSetting::OnBnClickedAddButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_Supplier.IsEmpty() || m_Model.IsEmpty() || m_MI.IsEmpty() 
		|| m_ATLLen.IsEmpty() || m_Qty.IsEmpty() || m_Material.IsEmpty())
	{
		AfxMessageBox("填写内容不能为空！");
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

	UpdateData(false);
}


void CBISSetting::OnBnClickedModButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	GetDlgItem(IDC_ADD_BUTTON)->EnableWindow(FALSE);

	if (m_Supplier.IsEmpty() || m_Model.IsEmpty() || m_MI.IsEmpty() 
		|| m_ATLLen.IsEmpty() || m_Qty.IsEmpty() || m_Material.IsEmpty())
	{
		AfxMessageBox("填写内容不能为空！");
		return;
	}

	CString sql = "update bBISInfo set Supplier='"+m_Supplier+"', ProductModel='"+m_Model+"',\
		BarcodeLen='"+m_ATLLen+"', Quantity='"+m_Qty+"', Material='"+m_Material+"' where ProductMI='"+m_MI+"'";

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
	m_Material = m_BISList.GetItemText(i,5);

	UpdateData(false);

	*pResult = 0;
}
