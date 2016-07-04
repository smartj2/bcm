// SubConPack.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SubConPack.h"
#include "afxdialogex.h"


// CSubConPack 对话框

IMPLEMENT_DYNAMIC(CSubConPack, CDialogEx)

CSubConPack::CSubConPack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSubConPack::IDD, pParent)
{

}

CSubConPack::~CSubConPack()
{
}

void CSubConPack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubConPack, CDialogEx)
END_MESSAGE_MAP()


// CSubConPack 消息处理程序
