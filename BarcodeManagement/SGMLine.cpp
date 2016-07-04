// SGMLine.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SGMLine.h"
#include "afxdialogex.h"


// CSGMLine 对话框

IMPLEMENT_DYNAMIC(CSGMLine, CDialogEx)

CSGMLine::CSGMLine(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSGMLine::IDD, pParent)
{

}

CSGMLine::~CSGMLine()
{
}

void CSGMLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSGMLine, CDialogEx)
END_MESSAGE_MAP()


// CSGMLine 消息处理程序
