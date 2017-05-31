// ProductReport.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "ProductReport.h"
#include "afxdialogex.h"


// CProductReport 对话框

IMPLEMENT_DYNAMIC(CProductReport, CDialogEx)

CProductReport::CProductReport(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProductReport::IDD, pParent)
{

}

CProductReport::~CProductReport()
{
}

void CProductReport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProductReport, CDialogEx)
END_MESSAGE_MAP()


// CProductReport 消息处理程序
