// Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "Login.h"
#include "afxdialogex.h"


// CLogin �Ի���
extern CBarcodeManagementApp theApp;

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
	ON_BN_CLICKED(IDCANCEL, &CLogin::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLogin ��Ϣ�������


BOOL CLogin::PreTranslateMessage(MSG* pMsg)
{
	// ȡ����������س��¼�
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
			UpdateData(true);
			if (m_UserName.IsEmpty() || m_PassWord.IsEmpty())
			{
				AfxMessageBox("�û��������벻��Ϊ��!");
				return FALSE;
			}

			CString sql = "select * from bUser where UserName='"+m_UserName+"' and UserPass='"+m_PassWord+"'";
			try
			{
				m_pRs.CreateInstance("ADODB.Recordset");
				m_pRs->Open((_variant_t)sql, theApp.m_pCon.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

				if (!m_pRs->adoEOF)
				{
					theApp.name = m_UserName;
					theApp.pwd  = m_PassWord;
					CDialog::OnOK();
				}
				else
				{
					AfxMessageBox("�û��������벻��ȷ!");
					// m_UserName = "";
					m_PassWord = "";
					UpdateData(false);
				}
			} catch(_com_error e)
			{
				CString eMessage;
				eMessage.Format("�������ݿ������Ϣ��%s", e.ErrorMessage());
				AfxMessageBox(eMessage);
			}
		}

		if (rc.PtInRect(point))
		{
			CDialogEx::OnCancel();
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CLogin::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
