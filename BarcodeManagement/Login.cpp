// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "Login.h"
#include "afxdialogex.h"


// CLogin 对话框

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


// CLogin 消息处理程序


BOOL CLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
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
				AfxMessageBox("用户名和密码不能为空!");
				return FALSE;
			}

			CString sql = "SELECT * FROM BCM_User WHERE BCM_User_Name='"+m_UserName+"' and BCM_User_Pswd='"+m_PassWord+"'";
			try
			{
				m_pRs.CreateInstance("ADODB.Recordset");
				m_pRs->Open((_variant_t)sql, theApp.m_pCon.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

				if (!m_pRs->adEOF)
				{
					theApp.name = m_UserName;
					theApp.pwd  = m_PassWord;
					CDialog::OnOK();
				}
				else
				{
					AfxMessageBox("用户名和密码不正确!");
					// m_UserName = "";
					m_PassWord = "";
					UpdateData(FALSE);
				}
			} catch(_com_error e)
			{
				CString temp;
				temp.Format("连接数据库错误信息：%s", e.Description());
				AfxMessageBox(temp);
			}
		}
		if (rc.PtInRect(point))
		{
			CDialog::OnCancel();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CLogin::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
