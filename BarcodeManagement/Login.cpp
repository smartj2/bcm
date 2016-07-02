// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "Login.h"
#include "afxdialogex.h"


// CLogin �Ի���

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
{
	m_UserName = _T("");
	m_PassWord = _T("");
}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_UserName);
	DDX_Text(pDX, IDC_EDIT2, m_PassWord);
	DDX_Control(pDX, IDOK, m_Login);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
END_MESSAGE_MAP()


// CLogin ��Ϣ�������


BOOL CLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
	{
		pMsg->wParam = 9;
	}
	if (pMsg->message == WM_LBUTTONDOWN)
	{
		CRect rect, rc;
		m_Login.GetWindowRect(&rect);
		m_Cancel.GetWindowRect(&rc);
		CPoint point;
		GetCursorPos(&point);
		if(rect.PtInRect(point))
		{
			UpdateData(TRUE);
			if (m_UserName.IsEmpty() || m_PassWord.IsEmpty())
			{
				MessageBox(_T("�û��������벻��Ϊ��!"));
				return FALSE;
			}
		}
		if (rc.PtInRect(point))
		{
			CDialog::OnCancel();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
