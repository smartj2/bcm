// SinglePack.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SinglePack.h"
#include "afxdialogex.h"


// CSinglePack 对话框

IMPLEMENT_DYNAMIC(CSinglePack, CDialogEx)

CSinglePack::CSinglePack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSinglePack::IDD, pParent)
{

}

CSinglePack::~CSinglePack()
{
}

void CSinglePack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSinglePack, CDialogEx)
END_MESSAGE_MAP()


// CSinglePack 消息处理程序


BOOL CSinglePack::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CSinglePack::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::PreTranslateMessage(pMsg);
}
