// SinglePack.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "SinglePack.h"
#include "afxdialogex.h"


// CSinglePack �Ի���

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


// CSinglePack ��Ϣ�������


BOOL CSinglePack::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CSinglePack::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialogEx::PreTranslateMessage(pMsg);
}
