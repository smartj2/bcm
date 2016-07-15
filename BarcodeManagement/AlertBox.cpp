// AlertBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "AlertBox.h"
#include "afxdialogex.h"


// CAlertBox �Ի���

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


// CAlertBox ��Ϣ�������


void CAlertBox::OnBnClickedConfirmButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	//CDialogEx::EndDialog(IDC_CONFIRM_BUTTON);
	return;
}


BOOL CAlertBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//GetDlgItem(IDC_INFO_STATIC)->SetWindowTextA("");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CAlertBox::PreTranslateMessage(MSG* pMsg)
{
	// ȡ����������س��¼�
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
