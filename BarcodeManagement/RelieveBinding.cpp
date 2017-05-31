// RelieveBinding.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "RelieveBinding.h"
#include "afxdialogex.h"


// CRelieveBinding 对话框

IMPLEMENT_DYNAMIC(CRelieveBinding, CDialogEx)

CRelieveBinding::CRelieveBinding(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRelieveBinding::IDD, pParent)
{

}

CRelieveBinding::~CRelieveBinding()
{
}

void CRelieveBinding::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRelieveBinding, CDialogEx)
END_MESSAGE_MAP()


// CRelieveBinding 消息处理程序
