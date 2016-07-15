// SubConPack.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SubConPack.h"
#include "AlertBox.h"
#include "afxdialogex.h"

#include <boost/regex.hpp>
#include <boost/format.hpp>

// CSubConPack 对话框
extern CBarcodeManagementApp theApp;
static int bnum = 1;
static int tray  = 1;

IMPLEMENT_DYNAMIC(CSubConPack, CDialogEx)

CSubConPack::CSubConPack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSubConPack::IDD, pParent)
	, m_MarkBox(_T(""))
	, m_Qty(_T(""))
	, m_ATLCode(_T(""))
	, m_MYCode(_T(""))
	, m_SGMQA(_T(""))
	, m_Remark(_T(""))
	, m_SGMLine(_T(""))
{

}

CSubConPack::~CSubConPack()
{
}

void CSubConPack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PACK_EDIT, m_MarkBox);
	DDX_Text(pDX, IDC_QTY_EDIT, m_Qty);
	DDX_Text(pDX, IDC_ATLCODE_EDIT, m_ATLCode);
	DDX_Text(pDX, IDC_MYCODE_EDIT, m_MYCode);
	DDX_Text(pDX, IDC_SGMQA_EDIT, m_SGMQA);
	DDX_Text(pDX, IDC_SGMLINE_EDIT, m_SGMLine);
	DDX_Text(pDX, IDC_REMARK_EDIT, m_Remark);
	DDX_Control(pDX, IDC_MODEL_COMBO, m_Model);
	DDX_Control(pDX, IDC_MI_COMBO, m_MI);
	DDX_Control(pDX, IDC_MATERIAL_COMBO, m_Material);
	DDX_Control(pDX, IDC_ATLLEN_COMBO, m_ATLLen);
	DDX_Control(pDX, IDC_MYLEN_COMBO, m_MYLen);
	DDX_Control(pDX, IDC_ATLWEEK_COMBO, m_ATLWeek);
	DDX_Control(pDX, IDC_MYWEEK_COMBO, m_MYWeek);
	DDX_Control(pDX, IDC_BCM_LIST, m_BCMList);
	DDX_Control(pDX, IDC_PACK_PROGRESS, m_PackProgress);
}


BEGIN_MESSAGE_MAP(CSubConPack, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CSubConPack::OnLbnSelchangeList1)
	ON_EN_KILLFOCUS(IDC_PACK_EDIT, &CSubConPack::OnEnKillfocusPackEdit)
	ON_EN_CHANGE(IDC_ATLCODE_EDIT, &CSubConPack::OnEnChangeAtlcodeEdit)
	ON_EN_CHANGE(IDC_MYCODE_EDIT, &CSubConPack::OnEnChangeMycodeEdit)
	ON_BN_CLICKED(IDC_PACK_BUTTON, &CSubConPack::OnBnClickedPackButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CSubConPack::OnBnClickedExitButton)
	ON_CBN_SELCHANGE(IDC_MODEL_COMBO, &CSubConPack::OnCbnSelchangeModelCombo)
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
	// 初始化ComBo
	//	m_Model.AddString("GB-S10-332029-010H");
	//	m_Model.SetCurSel(0);

	CString sql = "select * from bBISInfo";
	m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	if(m_pRs->GetRecordCount()==0)
	{
		return TRUE;
	}
	if(m_pRs->GetRecordCount()==1)
	{
		m_Model.AddString((char*)(_bstr_t)m_pRs->GetCollect("ProductModel"));
		//m_MI.AddString((char*)(_bstr_t)m_pRs->GetCollect("ProductMI"));
		//m_Material.AddString((char*)(_bstr_t)m_pRs->GetCollect("Material"));
		//m_ATLLen.AddString((char*)(_bstr_t)m_pRs->GetCollect("BarcodeLen"));
		return TRUE;
	}
	while(!m_pRs->adoEOF)
	{
		m_Model.AddString((char*)(_bstr_t)m_pRs->GetCollect("ProductModel"));
		//m_MI.AddString((char*)(_bstr_t)m_pRs->GetCollect("ProductMI"));
		//m_Material.AddString((char*)(_bstr_t)m_pRs->GetCollect("Material"));
		//m_ATLLen.AddString((char*)(_bstr_t)m_pRs->GetCollect("BarcodeLen"));
		m_pRs->MoveNext();
	}

	int week = 1;
	while (week <= 52)
	{
		std::string strWeek = boost::str(boost::format("%02d") % week);
		m_ATLWeek.AddString(String2CString(strWeek)); // 电芯周期
		m_MYWeek.AddString(String2CString(strWeek));  // 电池周期
		week = week + 1;
	}

	/*int WEEK_MAX = 7;
	for(int i=0; i < WEEK_MAX; ++i)
	{
		m_Day.AddString(Int2CString(i));
	}*/

	//m_MYLen.AddString("12");
	//m_MYLen.AddString("13");

	//for (int i = 0; i < 10; i++)
	//{
	//	std::string strLine = boost::str(boost::format("%s") % ('A'+i));
	//	m_SGMLine.AddString(String2CString(strLine)); // 电芯周期
	//}

	//m_SGMLine.AddString("A");
	//m_SGMLine.AddString("B");
	//m_SGMLine.AddString("C");
	//m_SGMLine.AddString("D");

	//GetDlgItem(IDC_QTY_EDIT)->SetWindowText("540");

	// 初始化默认选项
	m_Model.SetCurSel(0);
	//m_MI.SetCurSel(1);
	//m_Material.SetCurSel(1);
	//m_ATLLen.SetCurSel(0);
	//m_MYLen.SetCurSel(1);
	//m_SGMLine.SetCurSel(0);
	m_ATLWeek.SetCurSel(21);
	m_MYWeek.SetCurSel(27);

	m_BCMList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	// 设置表头
	m_BCMList.InsertColumn(0, "序号", LVCFMT_CENTER, 50, 0);
	m_BCMList.InsertColumn(1, "托盘号", LVCFMT_CENTER, 50, 1);
	m_BCMList.InsertColumn(2, "外箱条码", LVCFMT_CENTER, 100, 2);
	m_BCMList.InsertColumn(3, "电芯型号", LVCFMT_CENTER, 120, 3);
	m_BCMList.InsertColumn(4, "电芯条码", LVCFMT_CENTER, 120, 4);
	m_BCMList.InsertColumn(5, "电池条码", LVCFMT_CENTER, 120, 5);
	m_BCMList.InsertColumn(6, "品质检员", LVCFMT_CENTER, 100, 6);
	m_BCMList.InsertColumn(7, "扫码时间", LVCFMT_CENTER, 120, 7);
	m_BCMList.InsertColumn(8, "备注", LVCFMT_CENTER, 120, 8);

	GetDlgItem(IDC_PACK_EDIT)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CSubConPack::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSubConPack::OnEnKillfocusPackEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(true);
	//CString sql = "select * from bSubCon where MarkBox='"+m_MarkBox+"'";

	//try
	//{
	//	theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	//	if (!m_MarkBox.IsEmpty() && m_pRs->Fields->Count != 0)
	//	{
	//		AfxMessageBox("箱号已存在！");
	//		m_MarkBox = "";
	//		GetDlgItem(IDC_PACK_EDIT)->SetFocus();
	//		UpdateData(false);
	//		return;
	//	}
	//} catch(_com_error e)
	//{
	//	AfxMessageBox(e.Description());
	//}  
}


void CSubConPack::OnCbnSelchangeModelCombo()
{
	UpdateData(true);

	CString model;
	m_Model.GetLBText(m_Model.GetCurSel(), model);

	CString sql1 = "select * from bBISInfo where ProductModel='"+model+"'";
	try
	{
		m_pRs = theApp.m_pCon->Execute((_bstr_t)sql1,NULL,adCmdText);

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

	// 获取电池码长
	CString sql2 = "select * from bSGMInfo where ProductModel='"+model+"'";
	try
	{
		m_pRs = theApp.m_pCon->Execute((_bstr_t)sql2,NULL,adCmdText);

	} catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	
	if(!m_pRs->adoEOF)
	{
		m_MYLen.InsertString(0,(char*)(_bstr_t)m_pRs->GetCollect("MYLen"));
	}
	m_MYLen.SetCurSel(0);

	UpdateData(false);
}


void CSubConPack::OnEnChangeAtlcodeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);

	if (m_MarkBox == "")
	{
		AfxMessageBox("外箱条码不能为空!");
		m_ATLCode = "";
		m_MYCode =  "";
		UpdateData(false);
		GetDlgItem(IDC_PACK_EDIT)->SetFocus();
		return;
	}

	CString model;
	m_Model.GetLBText(m_Model.GetCurSel(), model);
	CString atlLen;
	m_ATLLen.GetLBText(m_ATLLen.GetCurSel(), atlLen);

	if (m_ATLCode.GetLength() == CString2Int(atlLen))
	{
		if (!CheckCoreCode(m_ATLCode))
		{
			AfxMessageBox("");
			AfxMessageBox("电芯码非法！！！");
			m_ATLCode = "";
			m_MYCode =  "";
			UpdateData(false);
			GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();
			return;
		}
		m_BCMList.InsertItem(bnum-1,"");
		m_BCMList.SetItemText(bnum-1,0,Int2CString(bnum));
		m_BCMList.SetItemText(bnum-1,1,Int2CString(tray));
		m_BCMList.SetItemText(bnum-1,2,m_MarkBox);
		m_BCMList.SetItemText(bnum-1,3,model);
		m_BCMList.SetItemText(bnum-1,4,m_ATLCode);
		
		m_MYCode =  "";
		UpdateData(false);

		GetDlgItem(IDC_MYCODE_EDIT)->SetFocus();
	}
}


void CSubConPack::OnEnChangeMycodeEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(true);

	if (m_ATLCode == "")
	{
		AfxMessageBox("");
		AfxMessageBox("请先扫电芯！");
		m_MYCode = "";
		UpdateData(false);

		GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();
		return;
	}

	CTime Time;
	Time = CTime::GetCurrentTime();
	CString scanTime = Time.Format("%Y-%m-%d %H:%M:%S");

	CString myLen;
	m_MYLen.GetLBText(m_MYLen.GetCurSel(), myLen);

	if (m_MYCode.GetLength() == CString2Int(myLen))
	{
		if (!CheckBatteryCode(m_MYCode))
		{
			AfxMessageBox("");
			AfxMessageBox("电池码非法！！！");
			m_ATLCode = "";
			m_MYCode = "";

			for (int i = 0; i < 5; i++)
			{
				m_BCMList.SetItemText(bnum-1,i,"");
			}

			UpdateData(false);

			GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();
			return;
		}
		m_BCMList.SetItemText(bnum-1,5,m_MYCode);
		m_BCMList.SetItemText(bnum-1,6,m_SGMQA);
		m_BCMList.SetItemText(bnum-1,7,scanTime);
		m_BCMList.SetItemText(bnum-1,8,m_Remark);
		
		//AfxMessageBox(m_ATLCode+","+m_MYCode);
		//将条码存入数据库
		CString sql = "insert into bDoubleBarcode(MarkBox,ATLBarcode,MYBarcode,ScanTime,Remark)\
					  values('"+m_MarkBox+"','"+m_ATLCode+"','"+m_MYCode+"','"+scanTime+"','"+m_Remark+"')";

		try
		{
			theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

		} catch(_com_error e)
		{
			//e.ErrorMessage();
			//AfxMessageBox(e.Description());
			AfxMessageBox("");
			AfxMessageBox("该电池重码！！！");
			m_ATLCode = "";
			m_MYCode = "";

			for (int i = 0; i < 9; i++)
			{
				m_BCMList.SetItemText(bnum-1,i,"");
			}

			UpdateData(false);
			GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();

			return;
		}

		//设置进度度
		m_PackProgress.SetRange(1, CString2Int(m_Qty));
		m_PackProgress.SetStep(1);
		m_PackProgress.StepIt();

		m_ATLCode =  "";
		UpdateData(false);

		GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();

		int tsize = CString2Int(TraySize);
		if (bnum%tsize == 0)
		{
			tray = tray + 1;
		}

		if (bnum == CString2Int(m_Qty))
		{
			AfxMessageBox("");
			AfxMessageBox("扫描完毕！请打包！");
			//将装箱信息存入数据库
			CString model;
			m_Model.GetLBText(m_Model.GetCurSel(), model);

			CString sql = "insert into bSubCon(ProductModel,MarkBox,MYLine,MYQA) \
						  values('"+model+"','"+m_MarkBox+"','"+m_SGMLine+"','"+m_SGMQA+"')";

			theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

			bnum++;
			m_MYCode =  "";
			UpdateData(false);
			return;
		}
	}
}


void CSubConPack::OnBnClickedPackButton()
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
		bnum = 1;   // 计数回到1
		tray = 1;
		m_MarkBox = "";
		//m_ATLCode = "";
		//m_MYCode = "";
		m_BCMList.DeleteAllItems();
		UpdateData(false);
		GetDlgItem(IDC_PACK_EDIT)->SetFocus();
		return;
	}
}


void CSubConPack::OnBnClickedExitButton()
{
	CDialogEx::OnCancel();
}


bool CSubConPack::CheckCoreCode(const CString& coreCode)
{
	using std::string;
	string strCoreCode = CString2String(coreCode);

	CString type;
	m_MI.GetLBText(m_MI.GetCurSel(), type);  //L41表示代号

	CString year = "6"; //6表示2016年
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
	boost::regex reg(strType + strYear + strWeek + "[0-9A-Z]{6}");
	return boost::regex_match(strCoreCode, reg);
}


bool CSubConPack::CheckBatteryCode(const CString& batteryCode)
{
	using std::string;
	string strBatteryCode = CString2String(batteryCode);

	CString type = "N";		   //N表示ATL
	string strType = CString2String(type);

	CString produceYear = "K"; //K表示2016年
	string strProduceYear=CString2String(produceYear);
	CString produceWeek;	   //04表示第4个星期
	m_ATLWeek.GetLBText(m_ATLWeek.GetCurSel(), produceWeek);
	string strProduceWeek = CString2String(produceWeek);
	strProduceWeek = boost::str( boost::format("%s%02d") % strProduceYear % strProduceWeek);

	CString company = "K";     //K表示Sigema
	string strCompany = CString2String(company);

	CString packageYear = "K"; //K表示2016年
	string strPackageYear=CString2String(packageYear);
	CString packageWeek;	   //09表示第9个星期
	m_MYWeek.GetLBText(m_MYWeek.GetCurSel(), packageWeek);
	string strPackageWeek = CString2String(packageWeek);
	strPackageWeek = boost::str( boost::format("%s%02d")% strPackageYear % strPackageWeek);

	CString locale = "B";      //B表示中国
	string strLocale = CString2String(locale);
	
	//1. 固定N
	//2. K04 生产周数
	//3. K
	//4. K09 组装周数
	//5. B+4位流水号
	boost::regex reg(strType + strProduceWeek + strCompany + strPackageWeek + strLocale + "[0-9A-Z]{4}");
	if( boost::regex_match(strBatteryCode, reg)==false)
	{
		return false;
	}

	//判断日期大小
	CString atlWeek; // atlWeek: 生产周期
	CString myWeek;  //  myWeek: 组装周期
	m_ATLWeek.GetLBText(m_ATLWeek.GetCurSel(), atlWeek);
	m_MYWeek.GetLBText(m_MYWeek.GetCurSel(), myWeek);
	if (CString2Int(atlWeek) > CString2Int(myWeek))
	{
		return false;
	}

	return true;
}


string CSubConPack::CString2String(const CString cStr)
{
	using std::string;
	string str = LPCSTR(cStr);

	return str;
}


CString CSubConPack::String2CString(const string str)
{
	CString cStr;
	cStr.Format("%s", str.c_str());

	return cStr;
}


int CSubConPack::CString2Int(const CString cStr)
{
	return atoi(cStr);
}


CString CSubConPack::Int2CString(const int num)
{
	CString temp;
	temp.Format(_T("%d"),num);

	return (LPCTSTR)temp;
}


