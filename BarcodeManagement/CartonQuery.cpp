// CartonQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "CartonQuery.h"
#include "afxdialogex.h"

#include <vector>
#include <string>
#include <boost/assign.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

// CCartonQuery 对话框
extern CBarcodeManagementApp theApp;

IMPLEMENT_DYNAMIC(CCartonQuery, CDialogEx)

CCartonQuery::CCartonQuery(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCartonQuery::IDD, pParent)
	, m_Query(_T(""))
{

}

CCartonQuery::~CCartonQuery()
{
}

void CCartonQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_QUERY_EDIT, m_Query);
	DDX_Control(pDX, IDC_RES_LIST, m_ResultList);
	DDX_Control(pDX, IDC_QTYPE_COMBO, m_QueryType);
}


BEGIN_MESSAGE_MAP(CCartonQuery, CDialogEx)
	ON_BN_CLICKED(IDC_QUERY_BUTTON, &CCartonQuery::OnBnClickedQueryButton)
	ON_BN_CLICKED(IDC_EXPORT_BUTTON, &CCartonQuery::OnBnClickedExportButton)
END_MESSAGE_MAP()


// CCartonQuery 消息处理程序


BOOL CCartonQuery::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_QueryType.AddString("外箱条码");
	m_QueryType.AddString("电芯条码");
	m_QueryType.AddString("电池条码");
	
	m_ResultList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	m_ResultList.InsertColumn(0,"电池型号",LVCFMT_CENTER,120,0);
	m_ResultList.InsertColumn(1,"外箱条码",LVCFMT_CENTER,100,1);
	m_ResultList.InsertColumn(2,"电芯条码",LVCFMT_CENTER,100,2);
	m_ResultList.InsertColumn(3,"电池条码",LVCFMT_CENTER,100,3);
	m_ResultList.InsertColumn(4,"操作员",LVCFMT_CENTER,60,4);
	m_ResultList.InsertColumn(5,"生产线/拉",LVCFMT_CENTER,80,5);
	m_ResultList.InsertColumn(6,"扫描时间",LVCFMT_CENTER,120,6);
	m_ResultList.InsertColumn(7,"备注信息",LVCFMT_CENTER,100,7);

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CCartonQuery::PreTranslateMessage(MSG* pMsg)
{
	// 取消键盘输入回车事件
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CCartonQuery::OnBnClickedQueryButton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_ResultList.DeleteAllItems();

	CString type;
	m_QueryType.GetLBText(m_QueryType.GetCurSel(), type);

	CString sql;
	if (type == "外箱条码")
	{
		sql = "select b.MarkBox, b.ATLBarcode, b.MYBarcode, b.ScanTime, b.Remark, \
			s.ProductModel, s.MYLine, s.MYQA from bDoubleBarcode b, bSubCon s where \
			b.MarkBox = s.MarkBox and b.MarkBox='"+m_Query+"'";
	}
	else if (type == "电芯条码")
	{
		sql = "select b.MarkBox, b.ATLBarcode, b.MYBarcode, b.ScanTime, b.Remark, \
			s.ProductModel, s.MYLine, s.MYQA from bDoubleBarcode b, bSubCon s where \
			b.MarkBox = s.MarkBox and b.ATLBarcode='"+m_Query+"'";
	}
	else if (type == "电池条码")
	{
		sql = "select b.MarkBox, b.ATLBarcode, b.MYBarcode, b.ScanTime, b.Remark, \
			s.ProductModel, s.MYLine, s.MYQA from bDoubleBarcode b, bSubCon s where \
			b.MarkBox = s.MarkBox and b.MYBarcode='"+m_Query+"'";
	}

	try
	{
		m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}
	UpdateData(FALSE);

	int i = 0;
	while(!m_pRs->adoEOF)
	{
		m_ResultList.InsertItem(i,"");
		m_ResultList.SetItemText(i,0,(char*)(_bstr_t)m_pRs->GetCollect("ProductModel"));
		m_ResultList.SetItemText(i,1,(char*)(_bstr_t)m_pRs->GetCollect("MarkBox"));
		m_ResultList.SetItemText(i,2,(char*)(_bstr_t)m_pRs->GetCollect("ATLBarcode"));
		m_ResultList.SetItemText(i,3,(char*)(_bstr_t)m_pRs->GetCollect("MYBarcode"));
		m_ResultList.SetItemText(i,4,(char*)(_bstr_t)m_pRs->GetCollect("MYQA"));
		m_ResultList.SetItemText(i,5,(char*)(_bstr_t)m_pRs->GetCollect("MYLine"));
		m_ResultList.SetItemText(i,6,(char*)(_bstr_t)m_pRs->GetCollect("ScanTime"));
		m_ResultList.SetItemText(i,7,(char*)(_bstr_t)m_pRs->GetCollect("Remark"));
		i++;

		m_pRs->MoveNext();
	}
}


void CCartonQuery::OnBnClickedExportButton()
{
	UpdateData(true);

	try
	{
		CString sql = "select b.MarkBox, b.ATLBarcode, b.MYBarcode, b.ScanTime, b.Remark, \
			s.ProductModel, s.MYLine, s.MYQA from bDoubleBarcode b, bSubCon s \
			where b.MarkBox = s.MarkBox and b.MarkBox='"+m_Query+"'";

		m_pRs = theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);
	}
	catch(_com_error e)
	{
		//AfxMessageBox(e.Description());
		AfxMessageBox("输入不正确！");
	}
	
	//boost::posix_time::ptime now= boost::posix_time::second_clock::local_time();
	//boost::gregorian::date nowDate = now.date();
	//boost::posix_time::time_duration nowTd =  now.time_of_day();
	//std::string filename = boost::str(boost::format("../exports/export_%4d%02d%02d_%02d%02d%02d.csv")
	//	%nowDate.year() % nowDate.month().as_number() % nowDate.day()
	//	%nowTd.hours() %nowTd.minutes() % nowTd.seconds());
	std::string fname = LPCSTR(m_Query);
	std::string filename = boost::str(boost::format("../exports/%1%.csv") %fname);
	
	namespace bf = boost::filesystem;

	if(!bf::exists("../exports"))
	{
		bf::create_directories("../exports");
	}

	bf::ofstream out(filename);
	std::vector<std::string>  keyWords =  boost::assign::list_of
		("ProductModel")
		("MarkBox")
		("ATLBarcode")
		("MYBarcode")
		("MYQA")
		("MYLine")
		("ScanTime")
		("Remark")
		;

	std::string title =boost::str(boost::format("%1%,%2%,%3%,%4%,%5%,%6%,%7%,%8%,%9%")
		%"序号"
		%"电池型号"
		%"外箱条码"
		%"电芯条码"
		%"电池条码"
		%"操作员"
		%"拉号"
		%"扫描时间"
		%"备注");

	out << title << std::endl;

	int i = 0;
	while(!m_pRs->adoEOF)
	{
		std::string temp = boost::str(boost::format("%1%") % (++i));
		BOOST_FOREACH(const std::string& keyWord, keyWords)
		{
			CString cstr_value = (char*)(_bstr_t)m_pRs->GetCollect(keyWord.c_str());
			std::string value = LPCSTR(cstr_value);
			if(temp.empty())
			{
				temp = value;
			}
			else
			{
				temp+=","+value;
			}
		}
		out << temp << std::endl;

		m_pRs->MoveNext();
	}

	out.close();
	AfxMessageBox("导出成功！");
}

