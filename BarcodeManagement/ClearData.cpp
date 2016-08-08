// ClearData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "ClearData.h"
#include "afxdialogex.h"


// CClearData �Ի���
extern CBarcodeManagementApp theApp;

IMPLEMENT_DYNAMIC(CClearData, CDialogEx)

CClearData::CClearData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClearData::IDD, pParent)
	, m_ClearBox(_T(""))
{

}

CClearData::~CClearData()
{
}

void CClearData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CLEARBOX_EDIT, m_ClearBox);
}


BEGIN_MESSAGE_MAP(CClearData, CDialogEx)
	ON_BN_CLICKED(IDOK, &CClearData::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CClearData::OnBnClickedCancel)
END_MESSAGE_MAP()


// CClearData ��Ϣ�������

BOOL CClearData::PreTranslateMessage(MSG* pMsg)
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


void CClearData::OnBnClickedOk()
{
	UpdateData(true);

	CString sql1 = "delete from bDoubleBarcode where MarkBox='"+m_ClearBox+"'";
	CString sql2 = "delete from bSingleBarcode where MarkBox='"+m_ClearBox+"'";

	try
	{
		theApp.m_pCon->Execute((_bstr_t)sql1,NULL,adCmdText);
		theApp.m_pCon->Execute((_bstr_t)sql2,NULL,adCmdText);
	} catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

	AfxMessageBox("����ɹ���");
	CDialogEx::OnOK();
}


void CClearData::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
