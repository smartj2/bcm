// AlertBox.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "AlertBox.h"
#include "afxdialogex.h"


// CAlertBox 对话框

IMPLEMENT_DYNAMIC(CAlertBox, CDialogEx)

CAlertBox::CAlertBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAlertBox::IDD, pParent)
{

}

CAlertBox::~CAlertBox()
{
}

void CAlertBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAlertBox, CDialogEx)
	ON_BN_CLICKED(IDC_CONFIRM_BUTTON, &CAlertBox::OnBnClickedConfirmButton)
END_MESSAGE_MAP()


// CAlertBox 消息处理程序


void CAlertBox::OnBnClickedConfirmButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	//CDialogEx::EndDialog(IDC_CONFIRM_BUTTON);
	return;
}


BOOL CAlertBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//GetDlgItem(IDC_INFO_STATIC)->SetWindowTextA("");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CAlertBox::PreTranslateMessage(MSG* pMsg)
{
	// 取消键盘输入回车事件
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}

	if (pMsg->message == WM_LBUTTONDOWN)
	{
		CDialogEx::OnOK();
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
