// SinglePack.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SinglePack.h"
#include "afxdialogex.h"

#include <boost/regex.hpp>
#include <boost/format.hpp>

// CSinglePack �Ի���
extern CBarcodeManagementApp theApp;
static int bnum = 1;
static int tray  = 1;

IMPLEMENT_DYNAMIC(CSinglePack, CDialogEx)

CSinglePack::CSinglePack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSinglePack::IDD, pParent)
	, m_MarkBox(_T(""))
	, m_Qty(_T(""))
	, m_SGMQA(_T(""))
	, m_Remark(_T(""))
	, m_ATLCode(_T(""))
	, TraySize(_T(""))
	, m_SGMLine(_T(""))
{

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


// CSinglePack ��Ϣ�������


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
		m_ATLWeek.AddString(String2CString(strWeek)); // ��о����
		week = week + 1;
	}

	//m_ATLLen.AddString("12");

	//m_SGMLine.AddString("A");
	//m_SGMLine.AddString("B");
	//m_SGMLine.AddString("C");
	//m_SGMLine.AddString("D");

	//m_Qty="540";

	// ��ʼ��Ĭ��ѡ��
	m_Model.SetCurSel(0);
	//m_MI.SetCurSel(1);
	//m_Material.SetCurSel(1);
	//m_ATLLen.SetCurSel(0);
	//m_SGMLine.SetCurSel(0);
	m_ATLWeek.SetCurSel(21);

	m_BCMList.SetExtendedStyle(LVS_EX_FLATSB
		|LVS_EX_FULLROWSELECT
		|LVS_EX_HEADERDRAGDROP
		|LVS_EX_ONECLICKACTIVATE
		|LVS_EX_GRIDLINES);

	// ���ñ�ͷ
	m_BCMList.InsertColumn(0, "���", LVCFMT_CENTER, 50, 0);
	m_BCMList.InsertColumn(1, "���̺�", LVCFMT_CENTER, 50, 1);
	m_BCMList.InsertColumn(2, "��������", LVCFMT_CENTER, 100, 2);
	m_BCMList.InsertColumn(3, "��о�ͺ�", LVCFMT_CENTER, 120, 3);
	m_BCMList.InsertColumn(4, "��о����", LVCFMT_CENTER, 120, 4);
	m_BCMList.InsertColumn(5, "Ʒ�ʼ�Ա", LVCFMT_CENTER, 100, 5);
	m_BCMList.InsertColumn(6, "ɨ��ʱ��", LVCFMT_CENTER, 120, 6);
	m_BCMList.InsertColumn(7, "��ע", LVCFMT_CENTER, 120, 7);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CSinglePack::PreTranslateMessage(MSG* pMsg)
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	UpdateData(true);

	CTime Time;
	Time = CTime::GetCurrentTime();
	CString scanTime = Time.Format("%Y-%m-%d %H:%M:%S");

	if (m_MarkBox == "")
	{
		AfxMessageBox("�������벻��Ϊ��!");
		m_ATLCode = "";
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
			AfxMessageBox("��о��Ƿ�������");
			m_ATLCode = "";
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
		m_BCMList.SetItemText(bnum-1,5,m_SGMQA);
		m_BCMList.SetItemText(bnum-1,6,scanTime);
		m_BCMList.SetItemText(bnum-1,7,m_Remark);

		//������������ݿ�
		CString sql = "insert into bSingleBarcode(MarkBox,ATLBarcode,ScanTime,Remark) \
			values('"+m_MarkBox+"','"+m_ATLCode+"','"+scanTime+"','"+m_Remark+"')";

		try
		{
			theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

		} catch(_com_error e)
		{
			//e.ErrorMessage();
			//AfxMessageBox(e.Description());
			AfxMessageBox("");
			AfxMessageBox("�õ�����룡����");
			m_ATLCode = "";

			for (int i = 0; i < 8; i++)
			{
				m_BCMList.SetItemText(bnum-1,i,"");
			}

			UpdateData(false);
			GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();
			return;
		}

		int tsize = CString2Int(TraySize);
		if (bnum%tsize == 0)
		{
			tray = tray + 1;
		}

		if (bnum == CString2Int(m_Qty))
		{
			AfxMessageBox("");
			AfxMessageBox("ɨ����ϣ�������");

			UpdateData(false);
		}

		bnum++;
		m_ATLCode = "";
		GetDlgItem(IDC_ATLCODE_EDIT)->SetFocus();
		UpdateData(false);
	}
}


void CSinglePack::OnBnClickedPackButton()
{
	UpdateData(true);

	if (bnum < CString2Int(m_Qty))
	{
		AfxMessageBox("������һ�䣬�����ɨ�裡");
		return;
	}
	else if (bnum-1 == CString2Int(m_Qty))
	{
		AfxMessageBox("����ɹ���");

		//��װ����Ϣ�������ݿ�
		CString model;
		m_Model.GetLBText(m_Model.GetCurSel(), model);

		CString sql = "insert into bSubCon(ProductModel,MarkBox,MYLine,MYQA) \
					  values('"+model+"','"+m_MarkBox+"','"+m_SGMLine+"','"+m_SGMQA+"')";
		try
		{
			theApp.m_pCon->Execute((_bstr_t)sql,NULL,adCmdText);

		} catch(_com_error e)
		{
			AfxMessageBox(e.Description());
		}

		bnum = 1;   // �����ص�1
		tray = 1;
		m_MarkBox = "";
		m_ATLCode = "";
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
	m_MI.GetLBText(m_MI.GetCurSel(), type);  //L41��ʾ����

	CString year = "6"; //6��ʾ2016��
	CString week;	   //04��ʾ��4������
	m_ATLWeek.GetLBText(m_ATLWeek.GetCurSel(), week);

	//CString dayInWeek;
	//m_Day.GetLBText(m_Day.GetCurSel(), dayInWeek); //4��ʾ������

	string strType = CString2String(type);
	string strYear = CString2String(year);
	string strWeek = CString2String(week);
	strWeek = boost::str(boost::format("%02d") % strWeek);
	//string strDayInWeek = CString2String(dayInWeek);

	//1.ǰ�����ַ�����һ���ģ���5λ��ˮ��
	boost::regex reg(strType + strYear + strWeek + "[0-9A-Z]{6}");
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


