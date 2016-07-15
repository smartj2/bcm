// SGMLine.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SGMLine.h"
#include "afxdialogex.h"


// CSGMLine 对话框
extern CBarcodeManagementApp theApp;

IMPLEMENT_DYNAMIC(CSGMLine, CDialogEx)

CSGMLine::CSGMLine(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSGMLine::IDD, pParent)
	, m_Model(_T(""))
	, m_BMI(_T(""))
	, m_Year(_T(""))
	, m_Capacity(_T(""))
	, m_MYLen(_T(""))
{

}

CSGMLine::~CSGMLine()
{
}

void CSGMLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SGM_LIST, m_SGMList);
	DDX_Text(pDX, IDC_MODEL_EDIT, m_Model);
	DDX_Text(pDX, IDC_SGMMI_EDIT, m_BMI);
	DDX_Text(pDX, IDC_YEAR_EDIT, m_Year);
	DDX_Text(pDX, IDC_CAPACITY_EDIT, m_Capacity);
	DDX_Text(pDX, IDC_MYLEN_EDIT, m_MYLen);
}


BEGIN_MESSAGE_MAP(CSGMLine, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CSGMLine::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_MOD_BUTTON, &CSGMLine::OnBnClickedModButton)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, &CSGMLine::OnBnClickedCancelButton)
	ON_NOTIFY(NM_DBLCLK, IDC_SGM_LIST, &CSGMLine::OnNMDblclkSgmList)
END_MESSAGE_MAP()


// CSGMLine 消息处理程序


BOOL CSGMLine::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_SGMList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_SGMList.InsertColumn(0,"电池型号",LVCFMT_CENTER,120,0);
	m_SGMList.InsertColumn(1,"电池MI",LVCFMT_CENTER,80,1);
	m_SGMList.InsertColumn(2,"组装年份",LVCFMT_CENTER,80,2);
	m_SGMList.InsertColumn(3,"电池容量",LVCFMT_CENTER,80,3);
	m_SGMList.InsertColumn(4,"电池码长",LVCFMT_CENTER,80,4);

	CString sql = "select * from bSGMInfo";
	try
	{
		m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	} catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

	int i = 0;
	while(!m_pRs->adoEOF)
	{
		m_SGMList.InsertItem(i,"");
		m_SGMList.SetItemText(i,0,(char*)(_bstr_t)m_pRs->GetCollect("ProductModel"));
		m_SGMList.SetItemText(i,1,(char*)(_bstr_t)m_pRs->GetCollect("BatteryMI"));
		m_SGMList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("ProduceYear"));
		m_SGMList.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("Capacity"));
		m_SGMList.SetItemText(i,4,(char*)(_bstr_t)m_pRs->GetCollect("MYLen"));
		i++;
		m_pRs->MoveNext();
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSGMLine::OnBnClickedAddButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_Model.IsEmpty() || m_BMI.IsEmpty() || m_Year.IsEmpty() || m_Capacity.IsEmpty() || m_MYLen.IsEmpty())
	{
		AfxMessageBox("填写内容不能为空！");
		return;
	}

	CString sql = "insert into bSGMInfo(ProductModel,BatteryMI,ProduceYear, \
		Capacity, MYLen) values('"+m_Model+"','"+m_BMI+"','"+m_Year+"','"+m_Capacity+"','"+m_MYLen+"')";

	theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	m_SGMList.DeleteAllItems();

	m_pRs = theApp.m_pCon->Execute((_bstr_t)("select * from bSGMInfo"),NULL,adCmdText);
	int i = 0;
	while(!m_pRs->adoEOF)
	{
		m_SGMList.InsertItem(i,"");
		m_SGMList.SetItemText(i,0,(char*)(_bstr_t)m_pRs->GetCollect("ProductModel"));
		m_SGMList.SetItemText(i,1,(char*)(_bstr_t)m_pRs->GetCollect("BatteryMI"));
		m_SGMList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("ProduceYear"));
		m_SGMList.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("Capacity"));
		m_SGMList.SetItemText(i,4,(char*)(_bstr_t)m_pRs->GetCollect("MYLen"));
		i++;
		m_pRs->MoveNext();
	}

	m_Model = "";
	m_BMI = "";
	m_Year = "";
	m_Capacity = "";
	m_MYLen = "";

	UpdateData(false);
}


void CSGMLine::OnBnClickedModButton()
{
	UpdateData(true);

	if (m_Model.IsEmpty() || m_BMI.IsEmpty() || m_Year.IsEmpty() || m_Capacity.IsEmpty() || m_MYLen.IsEmpty())
	{
		AfxMessageBox("填写内容不能为空！");
		return;
	}

	CString sql = "update bSGMInfo set ProductModel='"+m_Model+"', BatteryMI='"+m_BMI+"', \
		ProduceYear='"+m_Year+"', Capacity='"+m_Capacity+"', MYLen='"+m_MYLen+"' where ProductModel='"+m_Model+"'";

	try
	{
		theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

	} catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	
	m_SGMList.DeleteAllItems();

	m_pRs = theApp.m_pCon->Execute((_bstr_t)("select * from bSGMInfo"),NULL,adCmdText);
	int i = 0;
	while(!m_pRs->adoEOF)
	{
		m_SGMList.InsertItem(i,"");
		m_SGMList.SetItemText(i,0,(char*)(_bstr_t)m_pRs->GetCollect("ProductModel"));
		m_SGMList.SetItemText(i,1,(char*)(_bstr_t)m_pRs->GetCollect("BatteryMI"));
		m_SGMList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("ProduceYear"));
		m_SGMList.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("Capacity"));
		m_SGMList.SetItemText(i,4,(char*)(_bstr_t)m_pRs->GetCollect("MYLen"));
		i++;
		m_pRs->MoveNext();
	}

	m_Model = "";
	m_BMI = "";
	m_Year = "";
	m_Capacity = "";
	m_MYLen = "";

	UpdateData(false);
}


void CSGMLine::OnBnClickedCancelButton()
{
	CDialogEx::OnCancel();
}


void CSGMLine::OnNMDblclkSgmList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	int i = m_SGMList.GetSelectionMark();

	m_Model = m_SGMList.GetItemText(i,0);
	m_BMI = m_SGMList.GetItemText(i,1);
	m_Year = m_SGMList.GetItemText(i,2);
	m_Capacity = m_SGMList.GetItemText(i,3);
	m_MYLen = m_SGMList.GetItemText(i,4);

	UpdateData(false);

	*pResult = 0;
}
