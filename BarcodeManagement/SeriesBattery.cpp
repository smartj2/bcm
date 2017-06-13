// SeriesBattery.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SeriesBattery.h"
#include "afxdialogex.h"

#include <boost/regex.hpp>
#include <boost/format.hpp>

// CSeriesBattery 对话框
extern CBarcodeManagementApp theApp;

IMPLEMENT_DYNAMIC(CSeriesBattery, CDialogEx)

CSeriesBattery::CSeriesBattery(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSeriesBattery::IDD, pParent)
	, m_ATLCode1(_T(""))
	, m_ATLCode2(_T(""))
	, m_ClearCode(_T(""))
{
	bnum = 1;
}

CSeriesBattery::~CSeriesBattery()
{
}

void CSeriesBattery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ATLCODE1_EDIT, m_ATLCode1);
	DDX_Text(pDX, IDC_ATLCODE2_EDIT, m_ATLCode2);
	DDX_Control(pDX, IDC_MODEL_COMBO, m_Model);
	DDX_Control(pDX, IDC_ATLWEEK_COMBO, m_ATLWeek);
	DDX_Control(pDX, IDC_SATL_LIST, m_ATLList);
	DDX_Text(pDX, IDC_CLEAR_EDIT, m_ClearCode);
}


BEGIN_MESSAGE_MAP(CSeriesBattery, CDialogEx)
	ON_EN_CHANGE(IDC_ATLCODE1_EDIT, &CSeriesBattery::OnEnChangeAtlcode1Edit)
	ON_EN_CHANGE(IDC_ATLCODE2_EDIT, &CSeriesBattery::OnEnChangeAtlcode2Edit)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CSeriesBattery::OnBnClickedClearButton)
END_MESSAGE_MAP()


// CSeriesBattery 消息处理程序
BOOL CSeriesBattery::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString sql = "select * from bBISInfo";
	m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	if(m_pRs->GetRecordCount()==0)
	{
		return TRUE;
	}
	if(m_pRs->GetRecordCount()==1)
	{
		m_Model.AddString((char*)(_bstr_t)m_pRs->GetCollect("ProductModel"));
		return TRUE;
	}
	while(!m_pRs->adoEOF)
	{
		m_Model.AddString((char*)(_bstr_t)m_pRs->GetCollect("ProductModel"));
		m_pRs->MoveNext();
	}

	int week = 1;
	while (week <= 54)
	{
		std::string strWeek = boost::str(boost::format("%02d") % week);
		m_ATLWeek.AddString(String2CString(strWeek));   // 电芯周期
		week = week + 1;
	}

	// 初始化默认选项
	m_Model.SetCurSel(0);
	m_ATLWeek.SetCurSel(29);

	m_ATLList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	// 设置表头
	m_ATLList.InsertColumn(0, "序号", LVCFMT_CENTER, 50, 0);
	m_ATLList.InsertColumn(1, "电芯条码1", LVCFMT_CENTER, 150, 1);
	m_ATLList.InsertColumn(2, "电芯条码2", LVCFMT_CENTER, 150, 2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CSeriesBattery::PreTranslateMessage(MSG* pMsg)
{
	// 屏蔽键盘输入回车事件
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSeriesBattery::OnEnChangeAtlcode1Edit()
{
	UpdateData(true);

	CString model;
	m_Model.GetLBText(m_Model.GetCurSel(), model);

	CString sql = "select * from bBISInfo where ProductModel='"+model+"'";
	try
	{
		m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

	} catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

	CString len; //电芯码长
	len = (char*)(_bstr_t)m_pRs->GetCollect("BarcodeLen");

	if (m_ATLCode1.GetLength() == CString2Int(len))
	{
		if (!CheckCoreCode(m_ATLCode1))
		{
			AfxMessageBox("");
			AfxMessageBox("电芯码非法！！！");
			m_ATLCode1 =  "";
			UpdateData(false);
			GetDlgItem(IDC_ATLCODE1_EDIT)->SetFocus();
			return;
		}

		m_ATLList.InsertItem(bnum-1,"");
		m_ATLList.SetItemText(bnum-1,0,Int2CString(bnum));
		m_ATLList.SetItemText(bnum-1,1,m_ATLCode1);
		
		m_ATLCode2 =  "";
		UpdateData(false);

		GetDlgItem(IDC_ATLCODE2_EDIT)->SetFocus();
	}
}

void CSeriesBattery::OnEnChangeAtlcode2Edit()
{
	UpdateData(true);

	CString model;
	m_Model.GetLBText(m_Model.GetCurSel(), model);

	CString sql = "select * from bBISInfo where ProductModel='"+model+"'";
	try
	{
		m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

	} catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

	CString len; //电芯码长
	len = (char*)(_bstr_t)m_pRs->GetCollect("BarcodeLen");

	if (m_ATLCode2.GetLength() == CString2Int(len))
	{
		if (!CheckCoreCode(m_ATLCode2))
		{
			AfxMessageBox("");
			AfxMessageBox("电芯码非法！！！");
			m_ATLCode1 = "";
			m_ATLCode2 = "";

			for (int i = 0; i < 3; i++)
			{
				m_ATLList.SetItemText(bnum-1,i,"");
			}

			UpdateData(false);

			GetDlgItem(IDC_ATLCODE1_EDIT)->SetFocus();
			return;
		}

		if (m_ATLCode2 == m_ATLCode1)
		{
			AfxMessageBox("");
			AfxMessageBox("电芯码重码！！！");
			m_ATLCode1 = "";
			m_ATLCode2 = "";

			for (int i = 0; i < 3; i++)
			{
				m_ATLList.SetItemText(bnum-1,i,"");
			}

			UpdateData(false);

			GetDlgItem(IDC_ATLCODE1_EDIT)->SetFocus();
			return;
		}

		m_ATLList.SetItemText(bnum-1,2,m_ATLCode2);
		
		//判断是否有码重复
		CString u_sql = "select * from bSeriesBattery where ATLBarcode2='"+m_ATLCode1+"' \
			union select * from bSeriesBattery where ATLBarcode1='"+m_ATLCode2+"'";

		m_pRs = theApp.m_pCon->Execute((_bstr_t)u_sql,NULL,adCmdText);
		if(!m_pRs->adoEOF)
		{
			AfxMessageBox("");
			AfxMessageBox("该电池已重复扫码！！！");

			m_ATLCode1 = "";
			m_ATLCode2 = "";

			for (int i = 0; i < 3; i++) {
				m_ATLList.SetItemText(bnum-1,i,"");
			}

			UpdateData(false);
			GetDlgItem(IDC_ATLCODE1_EDIT)->SetFocus();
			return;
		}
		//将条码存入数据库
		CString sql = "insert into bSeriesBattery(ATLBarcode1,ATLBarcode2) \
			values('"+m_ATLCode1+"','"+m_ATLCode2+"')";

		try
		{
			theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

		} catch(_com_error e)
		{
			//AfxMessageBox(e.Description());
			AfxMessageBox("");
			AfxMessageBox("该电池重码！！！");
			m_ATLCode1 = "";
			m_ATLCode2 = "";

			for (int i = 0; i < 3; i++) {
				m_ATLList.SetItemText(bnum-1,i,"");
			}

			UpdateData(false);
			GetDlgItem(IDC_ATLCODE1_EDIT)->SetFocus();

			return;
		}

		m_ATLCode1 =  "";
		m_ATLCode2 =  "";

		GetDlgItem(IDC_ATLCODE1_EDIT)->SetFocus();

		bnum++;
		UpdateData(false);
	}
	// 实现CtrlList自动滚动
	m_ATLList.EnsureVisible(m_ATLList.GetItemCount()-1, TRUE);
}

bool CSeriesBattery::CheckCoreCode(const CString& coreCode)
{
	using std::string;
	string strCoreCode = CString2String(coreCode);

	CString model;
	m_Model.GetLBText(m_Model.GetCurSel(), model);

	CString sql = "select * from bBISInfo where ProductModel='"+model+"'";
	try
	{
		m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

	} catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

	CString MI; //MI
	MI = (char*)(_bstr_t)m_pRs->GetCollect("ProductMI");

	CString year; //6表示2016年
	year = (char*)(_bstr_t)m_pRs->GetCollect("ProduceYear");

	CString week;	   //04表示第4个星期
	m_ATLWeek.GetLBText(m_ATLWeek.GetCurSel(), week);

	//CString dayInWeek;
	//m_Day.GetLBText(m_Day.GetCurSel(), dayInWeek); //4表示星期四

	string strType = CString2String(MI);
	string strYear = CString2String(year);
	string strWeek = CString2String(week);
	strWeek = boost::str(boost::format("%02d") % strWeek);
	//string strDayInWeek = CString2String(dayInWeek);

	//1.前三个字符串是一样的，后5位流水号
	boost::regex reg(strType + strYear + strWeek + "[0-9A-Z]{6}");
	//boost::regex reg(strType + "[0-9A-Z]{9}");
	return boost::regex_match(strCoreCode, reg);
}


string CSeriesBattery::CString2String(const CString cStr)
{
	using std::string;
	string str = LPCSTR(cStr);

	return str;
}


CString CSeriesBattery::String2CString(const string str)
{
	CString cStr;
	cStr.Format("%s", str.c_str());

	return cStr;
}


int CSeriesBattery::CString2Int(const CString cStr)
{
	return atoi(cStr);
}


CString CSeriesBattery::Int2CString(const int num)
{
	CString temp;
	temp.Format(_T("%d"),num);

	return (LPCTSTR)temp;
}


void CSeriesBattery::OnBnClickedClearButton()
{
	UpdateData(true);
	CString sql1 = "delete from bSeriesBattery where ATLBarcode1='"+m_ClearCode+"'";
	CString sql2 = "delete from bSeriesBattery where ATLBarcode2='"+m_ClearCode+"'";

	try
	{
		theApp.m_pCon->Execute((_bstr_t)sql1,NULL,adCmdText);
		theApp.m_pCon->Execute((_bstr_t)sql2,NULL,adCmdText);
	} catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

	AfxMessageBox("清理成功！");
	m_ClearCode = "";
	UpdateData(false);
}
