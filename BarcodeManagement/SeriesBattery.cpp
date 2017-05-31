// SeriesBattery.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SeriesBattery.h"
#include "afxdialogex.h"


// CSeriesBattery 对话框

IMPLEMENT_DYNAMIC(CSeriesBattery, CDialogEx)

CSeriesBattery::CSeriesBattery(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSeriesBattery::IDD, pParent)
{

}

CSeriesBattery::~CSeriesBattery()
{
}

void CSeriesBattery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSeriesBattery, CDialogEx)
END_MESSAGE_MAP()


// CSeriesBattery 消息处理程序
