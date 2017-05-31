
// BarcodeManagementDlg.h : 头文件
//

#pragma once


// CBarcodeManagementDlg 对话框
class CBarcodeManagementDlg : public CDialogEx
{
// 构造
public:
	CMenu m_pMenu;
	CBarcodeManagementDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BARCODEMANAGEMENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBISSetting();
	afx_msg void OnSGMSetting();
	afx_msg void OnSingleMenu();
	afx_msg void OnCartonPacking();
	afx_msg void OnCartonQuery();
	afx_msg void OnClearMenu();
	afx_msg void OnAboutbox();
	afx_msg void OnSeriesMenu();
	afx_msg void OnTripleMenu();
	afx_msg void OnResolveMenu();
	afx_msg void OnReportMenu();
};
