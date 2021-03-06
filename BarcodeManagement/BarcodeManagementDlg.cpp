
// BarcodeManagementDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BarcodeManagement.h"
#include "BarcodeManagementDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include "BISSetting.h"
#include "SGMLine.h"
#include "SinglePack.h"
#include "SubConPack.h"
#include "CartonQuery.h"
#include "ClearData.h"
#include "AlertBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBarcodeManagementDlg 对话框

CBarcodeManagementDlg::CBarcodeManagementDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBarcodeManagementDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBarcodeManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBarcodeManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_COMMAND(ID_BIS_MENU, &CBarcodeManagementDlg::OnBISSetting)
	ON_COMMAND(ID_SGM_MENU, &CBarcodeManagementDlg::OnSGMSetting)
	ON_COMMAND(ID_SINGLE_MENU, &CBarcodeManagementDlg::OnSingleMenu)
	ON_COMMAND(ID_PACK_MENU, &CBarcodeManagementDlg::OnCartonPacking)
	ON_COMMAND(ID_INFO_MENU, &CBarcodeManagementDlg::OnCartonQuery)
	ON_COMMAND(IDD_ABOUTBOX, &CBarcodeManagementDlg::OnAboutbox)
	ON_COMMAND(ID_CLEAR_MENU, &CBarcodeManagementDlg::OnClearMenu)
END_MESSAGE_MAP()


// CBarcodeManagementDlg 消息处理程序

BOOL CBarcodeManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	/*CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}*/

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CLogin dlg;
	if (dlg.DoModal() == IDOK)
	{
		return FALSE;
	}
	if (dlg.DoModal() == IDCANCEL)
	{
		CDialogEx::OnCancel();
	}

	// 创建菜单
	//pMenu->GetSubMenu(1)->EnableMenuItem(1, MF_BYPOSITION | MF_GRAYED);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBarcodeManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBarcodeManagementDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBarcodeManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CBarcodeManagementDlg::OnBISSetting()
{
	CBISSetting dlg;
	dlg.DoModal();
}


void CBarcodeManagementDlg::OnSGMSetting()
{
	CSGMLine dlg;
	dlg.DoModal();
}


void CBarcodeManagementDlg::OnSingleMenu()
{
	CSinglePack dlg;
	dlg.DoModal();
}


void CBarcodeManagementDlg::OnCartonPacking()
{
	CSubConPack dlg;
	dlg.DoModal();
}


void CBarcodeManagementDlg::OnCartonQuery()
{
	CCartonQuery dlg;
	dlg.DoModal();
}


void CBarcodeManagementDlg::OnClearMenu()
{
	CClearData dlg;
	dlg.DoModal();
}


void CBarcodeManagementDlg::OnAboutbox()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

