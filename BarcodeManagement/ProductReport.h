#pragma once


// CProductReport 对话框

class CProductReport : public CDialogEx
{
	DECLARE_DYNAMIC(CProductReport)

public:
	CProductReport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProductReport();

// 对话框数据
	enum { IDD = IDD_REPORT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
