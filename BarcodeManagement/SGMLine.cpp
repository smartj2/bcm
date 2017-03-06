// SGMLine.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SGMLine.h"
#include "afxdialogex.h"


// CSGMLine �Ի���
extern CBarcodeManagementApp theApp;

IMPLEMENT_DYNAMIC(CSGMLine, CDialogEx)

CSGMLine::CSGMLine(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSGMLine::IDD, pParent)
	, m_Model(_T(""))
	, m_BMI(_T(""))
	, m_Year(_T(""))
	, m_Capacity(_T(""))
	, m_MYLen(_T(""))
	, m_ATLYear(_T(""))
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
	DDX_Text(pDX, IDC_ATLYEAR_EDIT, m_ATLYear);
}


BEGIN_MESSAGE_MAP(CSGMLine, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_BUTTON, &CSGMLine::OnBnClickedAddButton)
	ON_BN_CLICKED(IDC_MOD_BUTTON, &CSGMLine::OnBnClickedModButton)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, &CSGMLine::OnBnClickedCancelButton)
	ON_NOTIFY(NM_DBLCLK, IDC_SGM_LIST, &CSGMLine::OnNMDblclkSgmList)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CSGMLine::OnBnClickedDeleteButton)
END_MESSAGE_MAP()


// CSGMLine ��Ϣ�������


BOOL CSGMLine::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_SGMList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_SGMList.InsertColumn(0,"����ͺ�",LVCFMT_CENTER,120,0);
	m_SGMList.InsertColumn(1,"���MI",LVCFMT_CENTER,80,1);
	m_SGMList.InsertColumn(2,"������",LVCFMT_CENTER,60,2);
	m_SGMList.InsertColumn(3,"��о���",LVCFMT_CENTER,60,2);
	m_SGMList.InsertColumn(4,"�������",LVCFMT_CENTER,80,3);
	m_SGMList.InsertColumn(5,"����볤",LVCFMT_CENTER,80,4);

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
		m_SGMList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("PackYear"));
		m_SGMList.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("ProduceYear"));
		m_SGMList.SetItemText(i,4,(char*)(_bstr_t)m_pRs->GetCollect("Capacity"));
		m_SGMList.SetItemText(i,5,(char*)(_bstr_t)m_pRs->GetCollect("MYLen"));
		i++;
		m_pRs->MoveNext();
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSGMLine::OnBnClickedAddButton()
{
	UpdateData(true);
	if (m_Model.IsEmpty() || m_BMI.IsEmpty() || m_Year.IsEmpty() ||  m_ATLYear.IsEmpty() || m_Capacity.IsEmpty() || m_MYLen.IsEmpty())
	{
		AfxMessageBox("��д���ݲ���Ϊ�գ�");
		return;
	}

	CString sql = "insert into bSGMInfo(ProductModel,BatteryMI,ProduceYear,PackYear, \
		Capacity, MYLen) values('"+m_Model+"','"+m_BMI+"','"+m_ATLYear+"','"+m_Year+"','"+m_Capacity+"','"+m_MYLen+"')";

	theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	m_SGMList.DeleteAllItems();

	m_pRs = theApp.m_pCon->Execute((_bstr_t)("select * from bSGMInfo"),NULL,adCmdText);
	int i = 0;
	while(!m_pRs->adoEOF)
	{
		m_SGMList.InsertItem(i,"");
		m_SGMList.SetItemText(i,0,(char*)(_bstr_t)m_pRs->GetCollect("ProductModel"));
		m_SGMList.SetItemText(i,1,(char*)(_bstr_t)m_pRs->GetCollect("BatteryMI"));
		m_SGMList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("PackYear"));
		m_SGMList.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("ProduceYear"));
		m_SGMList.SetItemText(i,4,(char*)(_bstr_t)m_pRs->GetCollect("Capacity"));
		m_SGMList.SetItemText(i,5,(char*)(_bstr_t)m_pRs->GetCollect("MYLen"));
		i++;
		m_pRs->MoveNext();
	}

	m_Model = "";
	m_BMI = "";
	m_Year = "";
	m_Capacity = "";
	m_MYLen = "";
	m_ATLYear = "";

	UpdateData(false);
}


void CSGMLine::OnBnClickedModButton()
{
	UpdateData(true);

	if (m_Model.IsEmpty() || m_BMI.IsEmpty() || m_Year.IsEmpty() || m_ATLYear.IsEmpty() || m_Capacity.IsEmpty() || m_MYLen.IsEmpty())
	{
		AfxMessageBox("��д���ݲ���Ϊ�գ�");
		return;
	}

	CString sql = "update bSGMInfo set ProductModel='"+m_Model+"', BatteryMI='"+m_BMI+"', ProduceYear='"+m_ATLYear+"', \
		PackYear='"+m_Year+"', Capacity='"+m_Capacity+"', MYLen='"+m_MYLen+"' where ProductModel='"+m_Model+"'";

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
		m_SGMList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("PackYear"));
		m_SGMList.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("ProduceYear"));
		m_SGMList.SetItemText(i,4,(char*)(_bstr_t)m_pRs->GetCollect("Capacity"));
		m_SGMList.SetItemText(i,5,(char*)(_bstr_t)m_pRs->GetCollect("MYLen"));
		i++;
		m_pRs->MoveNext();
	}

	m_Model = "";
	m_BMI = "";
	m_Year = "";
	m_Capacity = "";
	m_MYLen = "";
	m_ATLYear = "";

	UpdateData(false);
}


void CSGMLine::OnBnClickedDeleteButton()
{
	UpdateData(true);

	CString sql="delete from bSGMInfo where ProductModel='"+m_Model+"'";
	
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
		m_SGMList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("PackYear"));
		m_SGMList.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("ProduceYear"));
		m_SGMList.SetItemText(i,4,(char*)(_bstr_t)m_pRs->GetCollect("Capacity"));
		m_SGMList.SetItemText(i,5,(char*)(_bstr_t)m_pRs->GetCollect("MYLen"));
		i++;
		m_pRs->MoveNext();
	}
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
	m_ATLYear = m_SGMList.GetItemText(i,5);

	UpdateData(false);

	*pResult = 0;
}

