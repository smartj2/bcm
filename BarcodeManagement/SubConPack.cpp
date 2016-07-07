// SubConPack.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SubConPack.h"
#include "afxdialogex.h"

#include <string>
#include <boost/regex.hpp>

// CSubConPack �Ի���
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


// CSubConPack ��Ϣ�������


void CSubConPack::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CSubConPack::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BCMList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);
	
	// ���ñ�ͷ
	m_BCMList.InsertColumn(0, "��������", LVCFMT_LEFT, 120, 0);
	m_BCMList.InsertColumn(0, "��Ʒ����", LVCFMT_LEFT, 150, 1);
	m_BCMList.InsertColumn(0, "�������", LVCFMT_LEFT, 150, 2);
	m_BCMList.InsertColumn(0, "��о����", LVCFMT_LEFT, 150, 3);
	m_BCMList.InsertColumn(0, "Ʒ�ʼ�Ա", LVCFMT_LEFT, 100, 4);
	m_BCMList.InsertColumn(0, "ɨ��ʱ��", LVCFMT_LEFT, 150, 5);

//	AddToGird();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CSubConPack::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

	if (count < 540)
	{
		AfxMessageBox("������һ�䣬�����ɨ�裡");
		return;
	}
	else if (count == 540)
	{
		AfxMessageBox("����ɹ���");
		count = 0;  // �����ص�0
		return;
	}
}


void CSubConPack::OnBnClickedExitButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//1.ǰ�����ַ�����һ���ģ���5λ��ˮ��
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

	//1.ǰ�����ַ�����һ���ģ���5λ��ˮ��
	boost::regex reg(strType+strProduceDate+strCompany+strPackageDate+"B[0-9A-Z]{4}");
	if( boost::regex_match(strBatteryCode, reg)==false)
	{
		return false;
	}

	string strDate1 = strProduceDate.substr(1,2);
	string strDate2 = strPackageDate.substr(1,2);
	//todo �ж����ڴ�С
	return true;
}
