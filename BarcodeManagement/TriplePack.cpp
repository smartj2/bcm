// TriplePack.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "TriplePack.h"
#include "afxdialogex.h"


// CTriplePack 对话框

IMPLEMENT_DYNAMIC(CTriplePack, CDialogEx)

CTriplePack::CTriplePack(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTriplePack::IDD, pParent)
{

}

CTriplePack::~CTriplePack()
{
}

void CTriplePack::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTriplePack, CDialogEx)
END_MESSAGE_MAP()


// CTriplePack 消息处理程序
