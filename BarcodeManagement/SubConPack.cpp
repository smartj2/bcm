// SubConPack.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SubConPack.h"
#include "afxdialogex.h"

#include <string>
#include <boost/regex.hpp>

// CSubConPack 对话框
extern CBarcodeManagementApp theApp;
static int count = 0;

IMPLEMENT_DYNAMIC(CSubConPack, CDialogEx)

CSubConPack::CSubConPack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSubConPack::IDD, pParent)
	, m_MarkBox(_T(""))
	, m_ATLCode(_T(""))
	, m_MYCode(_T(""))
{

}

CSubConPack::~CSubConPack()
{
}

void CSubConPack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PACK_EDIT, m_MarkBox);
	DDX_Control(pDX, IDC_MI_COMBO, m_MI);
	DDX_Control(pDX, IDC_QTY_COMBO, m_Qty);
	DDX_Text(pDX, IDC_ATLCODE_EDIT, m_ATLCode);
	DDX_Control(pDX, IDC_ATLLEN_COMBO, m_ATLLen);
	DDX_Control(pDX, IDC_ATLWEEK_COMBO, m_ATLWeek);
	DDX_Control(pDX, IDC_BCM_LIST, m_BCMList);
	DDX_Control(pDX, IDC_MATERIAL_COMBO, m_Material);
	DDX_Control(pDX, IDC_MODEL_COMBO, m_Model);
	DDX_Text(pDX, IDC_MYCODE_EDIT, m_MYCode);
	DDX_Control(pDX, IDC_MYLEN_COMBO, m_MYLen);
	DDX_Control(pDX, IDC_MYWEEK_COMBO, m_MYWeek);
	DDX_Control(pDX, IDC_SGMQA_COMB, m_SGMQA);
	DDX_Control(pDX, IDC_SGMLINE_COMBO, m_SGMLine);
}


BEGIN_MESSAGE_MAP(CSubConPack, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CSubConPack::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_ATLCODE_EDIT, &CSubConPack::OnEnChangeAtlcodeEdit)
	ON_EN_CHANGE(IDC_MYCODE_EDIT, &CSubConPack::OnEnChangeMycodeEdit)
	ON_BN_CLICKED(IDC_PACK_BUTTON, &CSubConPack::OnBnClickedPackButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CSubConPack::OnBnClickedExitButton)
END_MESSAGE_MAP()


// CSubConPack 消息处理程序


void CSubConPack::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CSubConPack::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_BCMList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	
	// 设置表头
	m_BCMList.InsertColumn(0, "外箱条码", LVCFMT_LEFT, 120, 0);
	m_BCMList.InsertColumn(0, "产品代码", LVCFMT_LEFT, 150, 1);
	m_BCMList.InsertColumn(0, "电池条码", LVCFMT_LEFT, 150, 2);
	m_BCMList.InsertColumn(0, "电芯条码", LVCFMT_LEFT, 150, 3);
	m_BCMList.InsertColumn(0, "品质检员", LVCFMT_LEFT, 100, 4);
	m_BCMList.InsertColumn(0, "扫码时间", LVCFMT_LEFT, 150, 5);

//	AddToGird();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CSubConPack::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSubConPack::OnEnChangeAtlcodeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CTime Time;
	Time = CTime::GetCurrentTime();
	CString scanTime = Time.Format("%Y-%m-%d %H:%M:%S");
//&& CheckCoreCode(m_ATLCode)
	if (m_ATLCode.GetLength() == 12)
	{
		m_BCMList.InsertItem(count,"");
		m_BCMList.SetItemText(count,3,m_ATLCode);
		m_BCMList.SetItemText(count,5,scanTime);
		
		m_MYCode =  "";
		UpdateData(FALSE);

		GetDlgItem(IDC_MYCODE_EDIT)->SetFocus();
	}
}


void CSubConPack::OnEnChangeMycodeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

//	CTime Time;
//	Time = CTime::GetCurrentTime();
//	CString scanTime = Time.Format("%Y-%m-%d %H:%M:%S");
// && CheckBatteryCode(m_MYCode)
	if (m_MYCode.GetLength() == 13)
	{
		//m_BCMList.InsertItem(count,"");
		m_BCMList.SetItemText(count,2,m_MYCode);

		count++;
		
		m_ATLCode =  "";
		UpdateData(FALSE);

		GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();
	}
}


void CSubConPack::OnBnClickedPackButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	if (count < 540)
	{
		AfxMessageBox("还不够一箱，请继续扫描！");
		return;
	}
	else if (count == 540)
	{
		AfxMessageBox("打包成功！");
		count = 0;  // 计数回到0
		return;
	}
}


void CSubConPack::OnBnClickedExitButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


bool CSubConPack::CheckCoreCode(const CString& coreCode)
{
	using std::string;
	string strCoreCode =coreCode.GetString();

	CString type;
	CString date;
	CString week;

	string strType = type.GetString();
	string strDate = date.GetString();
	string strWeek = date.GetString();
	//1.前三个字符串是一样的，后5位流水号
	boost::regex reg(strType+strDate+strWeek+"[0-9A-Z]{5}");
	return boost::regex_match(strCoreCode, reg);
}

bool CSubConPack::CheckBatteryCode(const CString& batteryCode)
{
	using std::string;
	string strBatteryCode = batteryCode.GetString();

	CString type;		    //N
	CString produceDate;	//K04
	CString company;	    //K
	CString packageDate;	//K09
	
	string strType = company.GetString();
	string strProduceDate = produceDate.GetString();
	string strCompany = company.GetString();
	string strPackageDate = packageDate.GetString();

	//1.前三个字符串是一样的，后5位流水号
	boost::regex reg(strType+strProduceDate+strCompany+strPackageDate+"B[0-9A-Z]{4}");
	if( boost::regex_match(strBatteryCode, reg)==false)
	{
		return false;
	}

	string strDate1 = strProduceDate.substr(1,2);
	string strDate2 = strPackageDate.substr(1,2);
	//todo 判断日期大小
	return true;
}
