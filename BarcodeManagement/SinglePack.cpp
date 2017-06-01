// SinglePack.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SinglePack.h"
#include "afxdialogex.h"

#include <boost/regex.hpp>
#include <boost/format.hpp>

// CSinglePack 对话框
extern CBarcodeManagementApp theApp;

IMPLEMENT_DYNAMIC(CSinglePack, CDialogEx)

CSinglePack::CSinglePack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSinglePack::IDD, pParent)
	, m_MarkBox(_T(""))
	, m_Qty(_T(""))
	, m_SGMQA(_T(""))
	, m_Remark(_T(""))
	, m_ATLCode(_T(""))
	, m_SGMLine(_T(""))
	, m_Current(_T("0"))
{

	bnum = 1;
	tray = 1;
}

CSinglePack::~CSinglePack()
{
}

void CSinglePack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PACK_EDIT, m_MarkBox);
	DDX_Text(pDX, IDC_QUANTITY_EDIT, m_Qty);
	DDX_Text(pDX, IDC_SGMQA_EDIT, m_SGMQA);
	DDX_Text(pDX, IDC_REMARK_EDIT, m_Remark);
	DDX_Text(pDX, IDC_ATLCODE_EDIT, m_ATLCode);
	DDX_Text(pDX, IDC_SGMLINE_EDIT, m_SGMLine);
	DDX_Text(pDX, IDC_CURRENT_EDIT, m_Current);
	DDX_Control(pDX, IDC_MODEL_COMBO, m_Model);
	DDX_Control(pDX, IDC_MI_COMBO, m_MI);
	DDX_Control(pDX, IDC_MATERAL_COMBO, m_Material);
	DDX_Control(pDX, IDC_ATLLEN_COMBO, m_ATLLen);
	DDX_Control(pDX, IDC_ATLWEEK_COMBO, m_ATLWeek);
	DDX_Control(pDX, IDC_BCM_LIST, m_BCMList);
}


BEGIN_MESSAGE_MAP(CSinglePack, CDialogEx)
	ON_CBN_SELCHANGE(IDC_MODEL_COMBO, &CSinglePack::OnCbnSelchangeModelCombo)
	ON_EN_CHANGE(IDC_ATLCODE_EDIT, &CSinglePack::OnEnChangeAtlcodeEdit)
	ON_BN_CLICKED(IDC_PACK_BUTTON, &CSinglePack::OnBnClickedPackButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CSinglePack::OnBnClickedExitButton)
END_MESSAGE_MAP()


// CSinglePack 消息处理程序


BOOL CSinglePack::OnInitDialog()
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

	m_BCMList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	// 设置表头
	m_BCMList.InsertColumn(0, "托盘号", LVCFMT_CENTER, 50, 0);
	m_BCMList.InsertColumn(1, "电池序号", LVCFMT_CENTER, 80, 1);
	m_BCMList.InsertColumn(2, "外箱条码", LVCFMT_CENTER, 100, 2);
	m_BCMList.InsertColumn(3, "电芯型号", LVCFMT_CENTER, 120, 3);
	m_BCMList.InsertColumn(4, "电芯条码", LVCFMT_CENTER, 120, 4);
	m_BCMList.InsertColumn(5, "品质检员", LVCFMT_CENTER, 100, 5);
	m_BCMList.InsertColumn(6, "扫码时间", LVCFMT_CENTER, 120, 6);
	m_BCMList.InsertColumn(7, "备注", LVCFMT_CENTER, 100, 7);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CSinglePack::PreTranslateMessage(MSG* pMsg)
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


void CSinglePack::OnCbnSelchangeModelCombo()
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
	
	if(!m_pRs->adoEOF)
	{
		m_MI.InsertString(0,(char*)(_bstr_t)m_pRs->GetCollect("ProductMI"));
		m_Material.InsertString(0,(char*)(_bstr_t)m_pRs->GetCollect("Material"));
		m_ATLLen.InsertString(0,(char*)(_bstr_t)m_pRs->GetCollect("BarcodeLen"));
		m_Qty   = (char*)(_bstr_t)m_pRs->GetCollect("Quantity");
		TraySize = (char*)(_bstr_t)m_pRs->GetCollect("TraySize");
	}

	m_MI.SetCurSel(0);
	m_Material.SetCurSel(0);
	m_ATLLen.SetCurSel(0);

	UpdateData(false);
}


void CSinglePack::OnEnChangeAtlcodeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(true);

	CTime Time;
	Time = CTime::GetCurrentTime();
	CString scanTime = Time.Format("%Y-%m-%d %H:%M:%S");

	if (m_MarkBox == "")
	{
		AfxMessageBox("外箱条码不能为空!");
		m_ATLCode = "";
		UpdateData(false);
		GetDlgItem(IDC_PACK_EDIT)->SetFocus();
		return;
	}

	CString model;
	m_Model.GetLBText(m_Model.GetCurSel(), model);
	CString atlLen;
	m_ATLLen.GetLBText(m_ATLLen.GetCurSel(), atlLen);

	int tsize = CString2Int(TraySize);

	if (m_ATLCode.GetLength() == CString2Int(atlLen))
	{
		if (!CheckCoreCode(m_ATLCode))
		{
			AfxMessageBox("");
			AfxMessageBox("电芯码非法！！！");
			m_ATLCode = "";
			UpdateData(false);
			GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();
			return;
		}

		int count = bnum%tsize;
		if (count == 0)
		{
			count = CString2Int(TraySize);
		}
		m_BCMList.InsertItem(bnum-1,"");
		m_BCMList.SetItemText(bnum-1,0,Int2CString(tray));
		m_BCMList.SetItemText(bnum-1,1,Int2CString(count));
		m_BCMList.SetItemText(bnum-1,2,m_MarkBox);
		m_BCMList.SetItemText(bnum-1,3,model);
		m_BCMList.SetItemText(bnum-1,4,m_ATLCode);
		m_BCMList.SetItemText(bnum-1,5,m_SGMQA);
		m_BCMList.SetItemText(bnum-1,6,scanTime);
		m_BCMList.SetItemText(bnum-1,7,m_Remark);

		//将条码存入数据库
		CString sql = "insert into bSingleBarcode(MarkBox,ATLBarcode,ScanTime,Remark) \
			values('"+m_MarkBox+"','"+m_ATLCode+"','"+scanTime+"','"+m_Remark+"')";

		try
		{
			theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

		} catch(_com_error e)
		{
			AfxMessageBox("");
			AfxMessageBox("该电池重码！！！");
			m_ATLCode = "";

			for (int i = 0; i < 8; i++)
			{
				m_BCMList.SetItemText(bnum-1,i,"");
			}

			UpdateData(false);
			GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();
			return;
		}

		if (count == CString2Int(TraySize) && tray < CString2Int(m_Qty)/CString2Int(TraySize))
		{
			AfxMessageBox("");
			AfxMessageBox("已扫完一盘，请换下一盘！");
		}

		if (bnum%tsize == 0)
		{
			tray = tray + 1;
		}

		if (bnum == CString2Int(m_Qty))
		{
			AfxMessageBox("");
			AfxMessageBox("扫描完毕！请打包！");

			UpdateData(false);
		}

		m_Current = Int2CString(bnum);
		bnum++;
		m_ATLCode = "";
		GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();
		UpdateData(false);
	}
	// 实现CtrlList自动滚动
	m_BCMList.EnsureVisible(m_BCMList.GetItemCount()-1, TRUE);
}


void CSinglePack::OnBnClickedPackButton()
{
	UpdateData(true);

	if (bnum < CString2Int(m_Qty))
	{
		AfxMessageBox("还不够一箱，请继续扫描！");
		return;
	}
	else if (bnum-1 == CString2Int(m_Qty))
	{
		AfxMessageBox("打包成功！");

		//将装箱信息存入数据库
		CString model;
		m_Model.GetLBText(m_Model.GetCurSel(), model);

		CString sql = "insert into bSubCon(ProductModel,MarkBox,MYLine,MYQA,IsDoubleCode) \
					  values('"+model+"','"+m_MarkBox+"','"+m_SGMLine+"','"+m_SGMQA+"','1')";
		try
		{
			theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

		} catch(_com_error e)
		{
			AfxMessageBox(e.Description());
		}

		bnum = 1;   // 计数回到1
		tray = 1;
		m_MarkBox = "";
		m_ATLCode = "";
		m_Current   = "";
		m_BCMList.DeleteAllItems();
		GetDlgItem(IDC_PACK_EDIT)->SetFocus();
		UpdateData(false);
		return;
	}
}


void CSinglePack::OnBnClickedExitButton()
{
	CDialogEx::OnCancel();
}


bool CSinglePack::CheckCoreCode(const CString& coreCode)
{
	using std::string;
	string strCoreCode = CString2String(coreCode);

	CString type;
	m_MI.GetLBText(m_MI.GetCurSel(), type);  //L41表示代号

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

	CString year; //6表示2016年
	year = (char*)(_bstr_t)m_pRs->GetCollect("ProduceYear");

	CString week;	   //04表示第4个星期
	m_ATLWeek.GetLBText(m_ATLWeek.GetCurSel(), week);

	//CString dayInWeek;
	//m_Day.GetLBText(m_Day.GetCurSel(), dayInWeek); //4表示星期四

	string strType = CString2String(type);
	string strYear = CString2String(year);
	string strWeek = CString2String(week);
	strWeek = boost::str(boost::format("%02d") % strWeek);
	//string strDayInWeek = CString2String(dayInWeek);

	//1.前三个字符串是一样的，后5位流水号
	//boost::regex reg(strType + strYear + strWeek + "[0-9A-Z]{6}");
	boost::regex reg(strType + "[0-9A-Z]{9}");
	return boost::regex_match(strCoreCode, reg);
}


string CSinglePack::CString2String(const CString cStr)
{
	using std::string;
	string str = LPCSTR(cStr);

	return str;
}


CString CSinglePack::String2CString(const string str)
{
	CString cStr;
	cStr.Format("%s", str.c_str());

	return cStr;
}


int CSinglePack::CString2Int(const CString cStr)
{
	return atoi(cStr);
}


CString CSinglePack::Int2CString(const int num)
{
	CString temp;
	temp.Format(_T("%d"),num);

	return (LPCTSTR)temp;
}


