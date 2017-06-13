// TriplePack.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "TriplePack.h"
#include "afxdialogex.h"

#include <boost/regex.hpp>
#include <boost/format.hpp>

// CTriplePack 对话框
extern CBarcodeManagementApp theApp;

IMPLEMENT_DYNAMIC(CTriplePack, CDialogEx)

CTriplePack::CTriplePack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTriplePack::IDD, pParent)
	, m_MarkBox(_T(""))
	, m_Qty(_T(""))
	, m_ATLCode(_T(""))
	, m_MYCode(_T(""))
	, m_SGMQA(_T(""))
	, m_SGMLine(_T(""))
	, m_Remark(_T(""))
	, m_Current(_T(""))
{
	bnum = 1;
	tray = 1;
}

CTriplePack::~CTriplePack()
{
}

void CTriplePack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PACK_EDIT, m_MarkBox);
	DDX_Text(pDX, IDC_QTY_EDIT, m_Qty);
	DDX_Text(pDX, IDC_ATLCODE_EDIT, m_ATLCode);
	DDX_Text(pDX, IDC_MYCODE_EDIT, m_MYCode);
	DDX_Text(pDX, IDC_SGMQA_EDIT, m_SGMQA);
	DDX_Text(pDX, IDC_SGMLINE_EDIT, m_SGMLine);
	DDX_Text(pDX, IDC_REMARK_EDIT, m_Remark);
	DDX_Text(pDX, IDC_CURRENT_EDIT, m_Current);
	DDX_Control(pDX, IDC_MODEL_COMBO, m_Model);
	DDX_Control(pDX, IDC_MI_COMBO, m_MI);
	DDX_Control(pDX, IDC_MATERIAL_COMBO, m_Material);
	DDX_Control(pDX, IDC_ATLLEN_COMBO, m_ATLLen);
	DDX_Control(pDX, IDC_MYLEN_COMBO, m_MYLen);
	DDX_Control(pDX, IDC_ATLWEEK_COMBO, m_ATLWeek);
	DDX_Control(pDX, IDC_MYWEEK_COMBO, m_MYWeek);
	DDX_Control(pDX, IDC_MYDAY_COMBO, m_MYDay);
	DDX_Control(pDX, IDC_BCM_LIST, m_BCMList);
	DDX_Control(pDX, IDC_PACK_PROGRESS, m_PackProgress);
}


BEGIN_MESSAGE_MAP(CTriplePack, CDialogEx)
	ON_CBN_SELCHANGE(IDC_MODEL_COMBO, &CTriplePack::OnCbnSelchangeModelCombo)
	ON_EN_CHANGE(IDC_ATLCODE_EDIT, &CTriplePack::OnEnChangeAtlcodeEdit)
	ON_EN_CHANGE(IDC_MYCODE_EDIT, &CTriplePack::OnEnChangeMycodeEdit)
	ON_BN_CLICKED(IDC_PACK_BUTTON, &CTriplePack::OnBnClickedPackButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CTriplePack::OnBnClickedExitButton)
END_MESSAGE_MAP()


// CTriplePack 消息处理程序

BOOL CTriplePack::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

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
		m_ATLWeek.AddString(String2CString(strWeek));  // 电芯周期
		m_MYWeek.AddString(String2CString(strWeek));   // 电池周期
		week = week + 1;
	}

	int day = 1;
	while (day <= 7)
	{
		m_MYDay.AddString(Int2CString(day));   // 电池周期
		day = day + 1;
	}

	// 初始化默认选项
	m_Model.SetCurSel(0);
	m_ATLWeek.SetCurSel(29);
	m_MYWeek.SetCurSel(35);
	m_MYDay.SetCurSel(2);

	m_BCMList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	// 设置表头
	m_BCMList.InsertColumn(0, "托盘号", LVCFMT_CENTER, 50, 0);
	m_BCMList.InsertColumn(1, "电池序号", LVCFMT_CENTER, 70, 1);
	m_BCMList.InsertColumn(2, "外箱条码", LVCFMT_CENTER, 100, 2);
	m_BCMList.InsertColumn(3, "电芯型号", LVCFMT_CENTER, 120, 3);
	m_BCMList.InsertColumn(4, "电池条码", LVCFMT_CENTER, 140, 4);
	m_BCMList.InsertColumn(5, "电芯型号1", LVCFMT_CENTER, 100, 5);
	m_BCMList.InsertColumn(6, "电芯型号2", LVCFMT_CENTER, 100, 6);
	m_BCMList.InsertColumn(7, "品质检员", LVCFMT_CENTER, 80, 7);
	m_BCMList.InsertColumn(8, "扫码时间", LVCFMT_CENTER, 120, 8);
	m_BCMList.InsertColumn(9, "备注", LVCFMT_CENTER, 100, 9);

	GetDlgItem(IDC_PACK_EDIT)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CTriplePack::PreTranslateMessage(MSG* pMsg)
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


void CTriplePack::OnCbnSelchangeModelCombo()
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

void CTriplePack::OnEnChangeMycodeEdit()
{
	UpdateData(true);

	if (m_MarkBox == "")
	{
		AfxMessageBox("外箱条码不能为空!");
		m_MYCode = "";
		m_ATLCode =  "";
		UpdateData(false);
		GetDlgItem(IDC_PACK_EDIT)->SetFocus();
		return;
	}

	CString model;
	m_Model.GetLBText(m_Model.GetCurSel(), model);
	CString myLen;
	m_MYLen.GetLBText(m_MYLen.GetCurSel(), myLen);

	int tsize = CString2Int(TraySize);

	if (m_MYCode.GetLength() == CString2Int(myLen))
	{
		if (!CheckBatteryCode(m_MYCode))
		{
			AfxMessageBox("");
			AfxMessageBox("电池码非法！！！");
			m_MYCode = "";
			m_ATLCode =  "";
			UpdateData(false);
			GetDlgItem(IDC_MYCODE_EDIT)->SetFocus();
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
		m_BCMList.SetItemText(bnum-1,4,m_MYCode);
		
		m_ATLCode =  "";
		UpdateData(false);

		GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();
	}
}

void CTriplePack::OnEnChangeAtlcodeEdit()
{
	UpdateData(true);

	if (m_MYCode == "")
	{
		AfxMessageBox("");
		AfxMessageBox("请先扫电池！");
		m_ATLCode = "";
		UpdateData(false);

		GetDlgItem(IDC_MYCODE_EDIT)->SetFocus();
		return;
	}

	CTime Time;
	Time = CTime::GetCurrentTime();
	CString scanTime = Time.Format("%Y-%m-%d %H:%M:%S");

	CString atlLen;
	m_ATLLen.GetLBText(m_ATLLen.GetCurSel(), atlLen);

	if (m_ATLCode.GetLength() == m_MYCode.GetLength() && m_ATLCode == m_MYCode)
	{
		AfxMessageBox("");
		AfxMessageBox("重复扫电池码，请换另一边！");

		m_ATLCode = "";

		UpdateData(false);

		GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();
		return;
	}

	if (m_ATLCode.GetLength() == CString2Int(atlLen))
	{
		if (!CheckCoreCode(m_ATLCode))
		{
			AfxMessageBox("");
			AfxMessageBox("电芯码非法！！！");
			m_MYCode = "";
			m_ATLCode = "";

			for (int i = 0; i < 5; i++)
			{
				m_BCMList.SetItemText(bnum-1,i,"");
			}

			UpdateData(false);

			GetDlgItem(IDC_MYCODE_EDIT)->SetFocus();
			return;
		}
		//获取另一个码，并插入
		CString ATLCode2 = "";
		CString sql1 = "select * from bSeriesBattery where ATLBarcode1='"+m_ATLCode+"'";
		CString sql2 = "select * from bSeriesBattery where ATLBarcode2='"+m_ATLCode+"'";
		// Search in ATLBarcode1
		try
		{
			m_pRs = theApp.m_pCon->Execute((_bstr_t)sql1,NULL,adCmdText);

		} catch(_com_error e)
		{
			AfxMessageBox(e.Description());
		}
	
		if(!m_pRs->adoEOF)
		{
			ATLCode2 = (char*)(_bstr_t)m_pRs->GetCollect("ATLBarcode2");
		}
		// Search in ATLBarcode2
		try
		{
			m_pRs = theApp.m_pCon->Execute((_bstr_t)sql2,NULL,adCmdText);

		} catch(_com_error e)
		{
			AfxMessageBox(e.Description());
		}
	
		if(!m_pRs->adoEOF)
		{
			ATLCode2 = (char*)(_bstr_t)m_pRs->GetCollect("ATLBarcode1");
		}

		if (ATLCode2 == "")
		{
			AfxMessageBox("");
			AfxMessageBox("电芯未绑定！！！");
			m_MYCode = "";
			m_ATLCode = "";

			for (int i = 0; i < 5; i++)
			{
				m_BCMList.SetItemText(bnum-1,i,"");
			}

			UpdateData(false);

			GetDlgItem(IDC_MYCODE_EDIT)->SetFocus();
			return;
		}

		m_BCMList.SetItemText(bnum-1,5,m_ATLCode);
		m_BCMList.SetItemText(bnum-1,6,ATLCode2);
		m_BCMList.SetItemText(bnum-1,7,m_SGMQA);
		m_BCMList.SetItemText(bnum-1,8,scanTime);
		m_BCMList.SetItemText(bnum-1,9,m_Remark);
		
		//将条码存入数据库
		CString sql = "insert into bTripleBarcode(MarkBox,ATLBarcode1,ATLBarcode2,MYBarcode,ScanTime,Remark)\
					  values('"+m_MarkBox+"','"+m_ATLCode+"','"+ATLCode2+"','"+m_MYCode+"','"+scanTime+"','"+m_Remark+"')";

		try
		{
			theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

		} catch(_com_error e)
		{
			//AfxMessageBox(e.Description());
			AfxMessageBox("");
			AfxMessageBox("该电池重码！！！");
			m_MYCode = "";
			m_ATLCode = "";

			for (int i = 0; i < 10; i++)
			{
				m_BCMList.SetItemText(bnum-1,i,"");
			}

			UpdateData(false);
			GetDlgItem(IDC_MYCODE_EDIT)->SetFocus();

			return;
		}

		//设置进度度
		m_PackProgress.SetRange(1, CString2Int(m_Qty));
		m_PackProgress.SetStep(1);
		m_PackProgress.StepIt();

		if (bnum%CString2Int(TraySize) == 0 && tray < CString2Int(m_Qty)/CString2Int(TraySize))
		{
			AfxMessageBox("");
			AfxMessageBox("已扫完一盘，请换下一盘！");
		}

		m_MYCode =  "";
		UpdateData(false);

		GetDlgItem(IDC_MYCODE_EDIT)->SetFocus();

		int tsize = CString2Int(TraySize);
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
		m_ATLCode =  "";
		GetDlgItem(IDC_MYCODE_EDIT)->SetFocus();
		UpdateData(false);
	}
	// 实现CtrlList自动滚动
	m_BCMList.EnsureVisible(m_BCMList.GetItemCount()-1, TRUE);
}

void CTriplePack::OnBnClickedPackButton()
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
						values('"+model+"','"+m_MarkBox+"','"+m_SGMLine+"','"+m_SGMQA+"','3')";

		theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

		bnum = 1;   // 计数回到1
		tray = 1;
		m_MarkBox = "";
		m_Current   = "";
		m_BCMList.DeleteAllItems();
		UpdateData(false);

		GetDlgItem(IDC_PACK_EDIT)->SetFocus();
		return;
	}
}


void CTriplePack::OnBnClickedExitButton()
{
	CDialogEx::OnCancel();
}

bool CTriplePack::CheckCoreCode(const CString& coreCode)
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

	CString year;  //6表示2016年
	year = (char*)(_bstr_t)m_pRs->GetCollect("ProduceYear");
	CString week;	   //04表示第4个星期
	//m_ATLWeek.GetLBText(m_ATLWeek.GetCurSel(), week);
	m_ATLWeek.GetWindowTextA(week);

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


bool CTriplePack::CheckBatteryCode(const CString& batteryCode)
{
	using std::string;
	string strBatteryCode = CString2String(batteryCode);

	CString model;
	m_Model.GetLBText(m_Model.GetCurSel(), model);

	CString sql = "select * from bSGMInfo where ProductModel='"+model+"'";
	try
	{
		m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

	} catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

	CString _model = (char*)(_bstr_t)m_pRs->GetCollect("ProductModel");
	//CString type = "N";		   //N表示ATL
	CString type =(char*)(_bstr_t)m_pRs->GetCollect("BatteryMI");
	string strType = CString2String(type);
	//CString year;  //6表示2016年
	CString produceYear = (char*)(_bstr_t)m_pRs->GetCollect("ProduceYear");
	CString packageYear = (char*)(_bstr_t)m_pRs->GetCollect("PackYear");
	CString capacity = (char*)(_bstr_t)m_pRs->GetCollect("Capacity");

	//CString produceYear = "K"; //K表示2016年
	string strProduceYear=CString2String(produceYear);
	CString produceWeek;	   //04表示第4个星期
	//m_ATLWeek.GetLBText(m_ATLWeek.GetCurSel(), produceWeek);
	m_ATLWeek.GetWindowTextA(produceWeek);
	string strProduceWeek = CString2String(produceWeek);
	strProduceWeek = boost::str( boost::format("%s%02d") % strProduceYear % strProduceWeek);

	CString company = "K";     //K表示Sigema
	string strCompany = CString2String(company);

	//CString packageYear = "K"; //K表示2016年
	string strPackageYear=CString2String(packageYear);
	CString packageWeek;	   //09表示第9个星期
	//m_MYWeek.GetLBText(m_MYWeek.GetCurSel(), packageWeek);
	m_MYWeek.GetWindowTextA(packageWeek);
	string strPackageWeek = CString2String(packageWeek);
	strPackageWeek = boost::str( boost::format("%s%02d")% strPackageYear % strPackageWeek);
	CString dayInWeek;
	//m_MYDay.GetLBText(m_MYDay.GetCurSel(), dayInWeek); //4表示星期四
	m_MYDay.GetWindowTextA(dayInWeek);
	string strDayInWeek = CString2String(dayInWeek);

	// 管控容量 
	string strCapacity=CString2String(capacity);
	strCapacity = boost::str( boost::format("%04d")% strCapacity);

	CString locale = "B";      //B表示中国
	string strLocale = CString2String(locale);
	
	//1. 固定N
	//2. K04 生产周数
	//3. K
	//4. K09 组装周数
	//5. B+4位流水号

	//[0-9A-Z]{1} 改为星期几
	if (model == "GB-S10-203440-0100")
	{
		boost::regex reg(strType + strPackageWeek + strDayInWeek + strProduceWeek + "[0-9A-Z]{4}" + "1" + strCapacity);
		if( boost::regex_match(strBatteryCode, reg)==false)
		{
			return false;
		}
	}
	else
	{
		boost::regex reg(strType + strProduceWeek + strCompany + strPackageWeek + strLocale + "[0-9A-Z]{4}");
		if( boost::regex_match(strBatteryCode, reg)==false)
		{
			return false;
		}
	}

	//判断日期大小
	CString atlWeek; // atlWeek: 生产周期
	CString myWeek;  //  myWeek: 组装周期
	//m_ATLWeek.GetLBText(m_ATLWeek.GetCurSel(), atlWeek);
	m_ATLWeek.GetWindowTextA(atlWeek);
	//m_MYWeek.GetLBText(m_MYWeek.GetCurSel(), myWeek);
	m_MYWeek.GetWindowTextA(myWeek);
	//TODO: 修复跨年
	//if (CString2Int(atlWeek) > CString2Int(myWeek)) //电池周期要大于电芯？
	//{
	//	return false;
	//}

	return true;
}


string CTriplePack::CString2String(const CString cStr)
{
	using std::string;
	string str = LPCSTR(cStr);

	return str;
}


CString CTriplePack::String2CString(const string str)
{
	CString cStr;
	cStr.Format("%s", str.c_str());

	return cStr;
}


int CTriplePack::CString2Int(const CString cStr)
{
	return atoi(cStr);
}


CString CTriplePack::Int2CString(const int num)
{
	CString temp;
	temp.Format(_T("%d"),num);

	return (LPCTSTR)temp;
}
