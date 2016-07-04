// BISSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "BISSetting.h"
#include "afxdialogex.h"


// CBISSetting 对话框

IMPLEMENT_DYNAMIC(CBISSetting, CDialogEx)

CBISSetting::CBISSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBISSetting::IDD, pParent)
{

}

CBISSetting::~CBISSetting()
{
}

void CBISSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBISSetting, CDialogEx)
END_MESSAGE_MAP()


// CBISSetting 消息处理程序
