// ProductReport.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "ProductReport.h"
#include "afxdialogex.h"


// CProductReport �Ի���

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


// CProductReport ��Ϣ�������
